#pragma once
class Enemy : public Object
{
public:
	Enemy();
	Enemy(int hp, int attack);
	virtual ~Enemy();

	void Update();
	void Render();

	void Fire();

	shared_ptr<Collider> GetCollider() { return _collider; }
	shared_ptr<Transform> GetTransform() { return _quad->GetTransform(); }

private:
	shared_ptr<Quad> _quad;
	shared_ptr<Collider> _collider;

	shared_ptr<Transform> _gunParent;
	shared_ptr<class Gun> _gun;
	shared_ptr<class Gun> _aim;

	vector<shared_ptr<class Bullet>> _bullets;

	UINT _poolCount = 30;
	float _time = 0.0f;
	float _maxTime = 0.3f;

	virtual void Attack(shared_ptr<Object> object) override;
};

