#include "framework.h"
#include "Enemy.h"

Enemy::Enemy()
{
	_quad = make_shared<Quad>(L"Resource/Enemy.png");
	_quad->GetTransform()->GetScale() = { 0.4f, 0.4f };
	_quad->GetTransform()->GetPos() = { CENTER.x, CENTER.y + 200 };

	_collider = make_shared<RectCollider>(_quad->GetHalfSize() * 0.15f);
	_collider->SetParent(_quad->GetTransform());
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	_quad->Update();
	_collider->Update();
}

void Enemy::Render()
{
	_quad->Render();
	_collider->Render();
}
