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

	_quad->Update();
	_collider->Update();
}

void Enemy::Render()
{
	if (_isActive == false)
		return;

	_quad->Render();
	_collider->Render();
}

void Enemy::Attack(shared_ptr<Object> object)
{
}
