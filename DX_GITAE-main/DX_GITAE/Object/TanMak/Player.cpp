#include "framework.h"
#include "Player.h"

Player::Player()
{
	_hp = 5;
	_attack = 1;

	_sprite = make_shared<Sprite>(L"Resource/Plane1.png", Vector2(5, 5));
	_sprite->GetTransform()->GetScale() = { 0.5f,0.5f };

	_collider = make_shared<RectCollider>(_sprite->GetFrameHalfSize());
	_collider->SetParent(_sprite->GetTransform());

	SetGunPosition();

	CreateActions();
	SetAnimation(_state);

	// Bullets
	for (int i = 0; i < _poolCount; i++)
	{
		shared_ptr<Bullet> bullet = make_shared<Bullet>();
		bullet->_isActive = false;

		_bullets.emplace_back(bullet);
	}
}

Player::Player(int hp, int attack)
{
	_hp = hp;
	_attack = attack;
}

Player::~Player()
{
}

void Player::Update()
{
	if (_isActive == false)
		return;

	KeyBoardMove();

	_time += DELTA_TIME;
	if (_time >= _maxTime)
	{
		_time = 0.0f;
		Fire();
	}

	_sprite->Update();
	_collider->Update();

	_gunParent->UpdateWorld();
	_gun->Update();
	_aim->Update();

	for (auto& action : _actions)
	{
		action->Update();
		if (action->IsPlay())
			_sprite->SetActionToActionBuffer(action->GetCurClip());
	}

	for (auto& bullet : _bullets)
		bullet->Update();

}

void Player::Render()
{
	if (_isActive == false)
		return;

	_sprite->Render();
	_collider->Render();

	for (auto& bullet : _bullets)
		bullet->Render();

}

void Player::PostRender()
{
	
}

void Player::Init()
{
	_sprite->GetTransform()->GetPos() = { CENTER.x , CENTER.y - 250 };

	for (auto& bullet : _bullets)
		bullet->_isActive = false;
}

void Player::CreateActions()
{
	vector<Action::Clip> clips;
	clips.reserve(10);
	float w = 1000.0f / 5.0f;
	float h = 1000.0f / 5.0f;

	// F_IDLE
	{
		clips.emplace_back(1000 * 0 + w * 2, 0, w, h, Texture::Add(L"Resource/Plane1.png"));
		clips.emplace_back(1000 * 0 + w * 2, 1, w, h, Texture::Add(L"Resource/Plane1.png"));
		clips.emplace_back(1000 * 0 + w * 2, 2, w, h, Texture::Add(L"Resource/Plane1.png"));
		shared_ptr<Action> action = make_shared<Action>(clips, "F_IDLE", Action::PINGPONG, 0.3f);
		action->Pause();
		_actions.push_back(action);
		clips.clear();
	}
	// L_MOVE
	{
		clips.emplace_back(1000 * 0 + w, 0, w, h, Texture::Add(L"Resource/Plane1.png"));
		clips.emplace_back(1000 * 0, 0, w, h, Texture::Add(L"Resource/Plane1.png"));
		shared_ptr<Action> action = make_shared<Action>(clips, "L_MOVE", Action::END, 0.3f);
		action->Pause();
		_actions.push_back(action);
		clips.clear();
	}
	// R_MOVE
	{
		clips.emplace_back(1000 * 0 + w * 3, 0, w, h, Texture::Add(L"Resource/Plane1.png"));
		clips.emplace_back(1000 * 0 + w * 4, 0, w, h, Texture::Add(L"Resource/Plane1.png"));
		shared_ptr<Action> action = make_shared<Action>(clips, "R_MOVE", Action::END, 0.3f);
		action->Pause();
		_actions.push_back(action);
		clips.clear();
	}
}

void Player::SetIDLE()
{
	switch (_state)
	{
	case Player::F_IDLE:
		SetAnimation(F_IDLE);
		break;
	case Player::L_MOVE:
		SetAnimation(F_IDLE);
		break;
	case Player::R_MOVE:
		SetAnimation(F_IDLE);
		break;
	default:
		break;
	}
}

void Player::KeyBoardMove()
{
	if (KEY_PRESS(VK_UP))
	{
		_sprite->GetTransform()->GetPos().y += _speed * DELTA_TIME;
		SetAnimation(Player::State::F_IDLE);
		return;
	}

	if (KEY_PRESS(VK_DOWN))
	{
		_sprite->GetTransform()->GetPos().y -= _speed * DELTA_TIME;
		SetAnimation(Player::State::F_IDLE);
		return;
	}

	if (KEY_PRESS(VK_LEFT))
	{
		_sprite->GetTransform()->GetPos().x -= _speed * DELTA_TIME;
		SetAnimation(Player::State::L_MOVE);
		return;
	}

	if (KEY_PRESS(VK_RIGHT))
	{
		_sprite->GetTransform()->GetPos().x += _speed * DELTA_TIME;
		SetAnimation(Player::State::R_MOVE);
		return;
	}

	SetIDLE();
}

void Player::Fire()
{
	if (KEY_PRESS(VK_CONTROL))
	{
		for (auto& bullet : _bullets)
		{
			if (bullet->_isActive == false)
			{
				bullet->_isActive = true;
				bullet->SetSpeed(700.0f);
				bullet->GetTransform()->GetPos() = _gunParent->GetWorldPos();
				Vector2 dir = _aim->GetTransform()->GetWorldPos() - _gunParent->GetWorldPos();
				dir.Normalize();
				bullet->SetDirection(dir);
				break;
			}
		}
	}

}

void Player::SetAnimation(Player::State state)
{
	if (_actions[state]->IsPlay() &&
		(_actions[state]->GetRepeatType() == Action::LOOP || _actions[state]->GetRepeatType() == Action::PINGPONG))
		return;

	for (auto& action : _actions)
	{
		if (action->IsPlay() && _state == state)
		{
			continue;
		}

		action->Reset();
	}

	_state = state;
	_actions[static_cast<UINT>(state)]->Play();
}

void Player::SetGunPosition()
{
	_gunParent = make_shared<Transform>();
	_gunParent->SetParent(_sprite->GetTransform());

	_gun = make_shared<Gun>();
	_gun->SetPlayer(_gunParent);

	_aim = make_shared<Gun>();
	_aim->SetPlayer(_gunParent);
	_aim->GetTransform()->GetPos().y += 300.0f;
}

void Player::Attack(shared_ptr<Object> object)
{
}
