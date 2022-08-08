#pragma once
class Enemy : public Object
{
public:
	Enemy();
	Enemy(int hp, int attack);
	virtual ~Enemy();

	void Update();
	void Render();

	shared_ptr<Collider> GetCollider() { return _collider; }
	shared_ptr<Transform> GetTransform() { return _quad->GetTransform(); }

private:
	shared_ptr<Quad> _quad;
	shared_ptr<Collider> _collider;

	virtual void Attack(shared_ptr<Object> object) override;
};

