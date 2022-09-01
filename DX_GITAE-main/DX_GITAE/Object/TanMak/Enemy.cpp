#include "framework.h"
#include "Enemy.h"

Enemy::Enemy()
{
	_hp = 10;
	_attack = 1;

	_quad = make_shared<Quad>(L"Resource/Enemy.png");
	_quad->GetTransform()->GetScale() = { 0.4f, 0.4f };
	_quad->GetTransform()->GetPos() = { CENTER.x, CENTER.y + 200 };

	_collider = make_shared<RectCollider>(_quad->GetHalfSize() * 0.15f);
	_collider->SetParent(_quad->GetTransform());

	_gunParent = make_shared<Transform>();
	_gunParent->SetParent(_quad->GetTransform());

	_gun = make_shared<Gun>();
	_gun->SetPlayer(_gunParent);

	_aim = make_shared<Gun>();
	_aim->SetPlayer(_gunParent);
	_aim->GetTransform()->GetPos().x += 300.0f;

	for (int i = 0; i < _poolCount; i++)
	{
		shared_ptr<Bullet> bullet = make_shared<Bullet>();
		bullet->_isActive = false;
		bullet->SetSpeed(200);

		_bullets.emplace_back(bullet);
	}
}

Enemy::Enemy(int hp, int attack)
{
	_hp = hp;
	_attack = attack;
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	if (_isActive == false)
		return;

	_gunParent->GetAngle() += DELTA_TIME;
	_time += DELTA_TIME;
	if (_time >= _maxTime)
	{
		_time = 0.0f;
		Fire();
	}


	_quad->Update();
	_collider->Update();

	_gunParent->UpdateWorld();
	_gun->Update();
	_aim->Update();

	for (auto& bullet : _bullets)
		bullet->Update();
}

void Enemy::Render()
{
	if (_isActive == false)
		return;

	_quad->Render();
	_collider->Render();

	_gun->Render();

	for (auto& bullet : _bullets)
		bullet->Render();
}

void Enemy::Fire()
{
	for (auto& bullet : _bullets)
	{
		if (bullet->_isActive == false)
		{
			bullet->_isActive = true;
			bullet->GetTransform()->GetPos() = _gunParent->GetWorldPos();
			Vector2 dir = _aim->GetTransform()->GetWorldPos() - _gunParent->GetWorldPos();
			dir.Normalize();
			bullet->SetDirection(dir);
			break;
		}
	}
}

void Enemy::Init()
{
	for (auto& bullet : _bullets)
		bullet->_isActive = false;
}

void Enemy::Attack(shared_ptr<Object> object)
{
}
