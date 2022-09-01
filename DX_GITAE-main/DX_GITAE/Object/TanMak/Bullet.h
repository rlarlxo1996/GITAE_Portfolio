#pragma once
class Bullet
{
public:
	Bullet();
	~Bullet();

	void Update();
	void Render();

	shared_ptr<Transform> GetTransform() { return _quad->GetTransform(); }
	shared_ptr<Collider>& GetCollider() { return _col; }

	void SetDirection(const Vector2& direction);
	void SetAngleDirect(const float& angle);
	void SetSpeed(float speed) { _speed = speed; }

	bool _isActive = false;
	int _attack = 1;
private:
	shared_ptr<Quad> _quad;
	shared_ptr<Collider> _col;

	Vector2 _direction = { 0,0 };
	float _speed = 500.0f;
	float _runTime = 0.0f;
	float _delayTime = 5.0f;
	float _angle = 0;
};

