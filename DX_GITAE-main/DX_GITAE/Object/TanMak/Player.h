#pragma once
class Player : public Object
{
public:
	enum State
	{
		F_IDLE,
		L_MOVE,
		R_MOVE
	};

	Player();
	Player(int hp, int attack);
	~Player();

	void Update();
	void Render();
	void PostRender();

	void Init();

	void CreateActions();
	void SetIDLE();
	void KeyBoardMove();
	void Fire();

	shared_ptr<Transform> GetTransform() { return _sprite->GetTransform(); }
	void SetPosition(Vector2 pos) { _sprite->GetTransform()->GetPos() = pos; }
	vector<shared_ptr<class Bullet>>& GetBullet() { return _bullets; }
	shared_ptr<Collider> GetCollider() { return _collider; }
	void SetAnimation(Player::State state);

	void SetGunPosition();

private:
	shared_ptr<Sprite> _sprite;
	shared_ptr<Collider> _collider;

	vector<shared_ptr<Action>> _actions;

	shared_ptr<Transform> _gunParent;
	shared_ptr<class Gun> _gun;
	shared_ptr<class Gun> _aim;

	vector<shared_ptr<class Bullet>> _bullets;

	State _state = State::F_IDLE;
	UINT _poolCount = 30;

	float _speed = 350.0f;
	float _time = 0.0f;
	float _maxTime = 0.2f;

	virtual void Attack(shared_ptr<Object> object) override;
};

