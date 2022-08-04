#include "framework.h"
#include "Player.h"

Player::Player()
{
	_sprite = make_shared<Sprite>(L"Resource/Plane1.png", Vector2(5, 5));
	_sprite->GetTransform()->GetScale() = { 0.5f,0.5f };

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

Player::~Player()
{
}

void Player::Update()
{
	KeyBoardMove();

	_time += DELTA_TIME;
	if (_time >= _maxTime)
	{
		_time = 0.0f;
		Fire();
	}

	_sprite->Update();
	_gunParent1->UpdateWorld();
	_gun1->Update();

	_gunParent2->UpdateWorld();
	_gun2->Update();

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
	_sprite->Render();
	_gun1->Render();
	_gun2->Render();

	for (auto& bullet : _bullets)
		bullet->Render();
}

void Player::PostRender()
{
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
	SetPosition(_pos);

	if (KEY_PRESS('W'))
	{
		_pos.y += _speed * DELTA_TIME;
		SetAnimation(Player::State::F_IDLE);
		return;
	}

	if (KEY_PRESS('S'))
	{
		_pos.y -= _speed * DELTA_TIME;
		SetAnimation(Player::State::F_IDLE);
		return;
	}

	if (KEY_PRESS('A'))
	{
		_pos.x -= _speed * DELTA_TIME;
		SetAnimation(Player::State::L_MOVE);
		return;
	}

	if (KEY_PRESS('D'))
	{
		_pos.x += _speed * DELTA_TIME;
		SetAnimation(Player::State::R_MOVE);
		return;
	}

	SetIDLE();
}

void Player::Fire()
{
	for (auto& bullet : _bullets)
	{
		if (bullet->_isActive == false)
		{
			bullet->_isActive = true;
			bullet->GetTransform()->GetPos() = _gunParent1->GetWorldPos();
			Vector2 dir = MOUSE_WORLD_POS - _gunParent1->GetWorldPos();
			dir.Normalize();
			bullet->SetDirection(dir);
			break;
		}
	}

	for (auto& bullet : _bullets)
	{
		if (bullet->_isActive == false)
		{
			bullet->_isActive = true;
			bullet->GetTransform()->GetPos() = _gunParent2->GetWorldPos();
			Vector2 dir = MOUSE_WORLD_POS - _gunParent2->GetWorldPos();
			dir.Normalize();
			bullet->SetDirection(dir);
			break;
		}
	}
}

void Player::SetAnimation(Player::State state)
{
	if (_actions[state]->IsPlay() &&
		(_actions[state]->GetReapeatTyoe() == Action::LOOP || _actions[state]->GetReapeatTyoe() == Action::PINGPONG))
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
	_gunParent1 = make_shared<Transform>();
	_gunParent1->SetParent(_sprite->GetTransform());

	_gun1 = make_shared<Gun>();
	_gun1->SetPlayer(_gunParent1);

	_gunParent2 = make_shared<Transform>();
	_gunParent2->SetParent(_sprite->GetTransform());
	_gunParent2->GetPos().x = -60.0f;

	_gun2 = make_shared<Gun>();
	_gun2->SetPlayer(_gunParent2);

	_gunParent3 = make_shared<Transform>();
}
