#pragma once
class Enemy
{
public:
	Enemy();
	~Enemy();

	void Update();
	void Render();

	shared_ptr<Collider> GetCollider() { return _collider; }

private:
	shared_ptr<Quad> _quad;
	shared_ptr<Collider> _collider;
};

