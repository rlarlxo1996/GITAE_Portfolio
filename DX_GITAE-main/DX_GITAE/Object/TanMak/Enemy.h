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

	vector<shared_ptr<class Bullet>> _bullets;

	UINT _poolCount = 30;
	float _time = 0.0f;
	float _maxTime = 0.4f;

	float _angle = 360.0f;

	virtual void Attack(shared_ptr<Object> object) override;
};

