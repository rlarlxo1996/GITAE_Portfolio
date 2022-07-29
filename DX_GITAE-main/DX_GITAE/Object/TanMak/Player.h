#pragma once
class Player
{
public:
	enum State
	{
		F_IDLE,
		L_MOVE,
		R_MOVE
	};

	Player();
	~Player();

	void Update();
	void Render();
	void PostRender();

	void CreateActions();
	void SetIDLE();
	void KeyBoardMove();
	void Fire();
	void SetGun();

	shared_ptr<Transform> GetTransform() { return _sprite->GetTransform(); }
	void SetPosition(Vector2 pos) { _sprite->GetTransform()->GetPos() = pos; }
	vector<shared_ptr<class Bullet>>& GetBullet() { return _bullets; }
	void SetAnimation(Player::State state);

	Vector2 _pos = Vector2(CENTER);
private:
	shared_ptr<Sprite> _sprite;

	vector<shared_ptr<Action>> _actions;
	shared_ptr<Transform> _gunParent;
	shared_ptr<class Gun> _gun;
	vector<shared_ptr<class Bullet>> _bullets;

	State _state = State::F_IDLE;
	UINT _poolCount = 30;

	float _speed = 350.0f;
	float _time = 0.0f;
	float _maxTime = 1.0f;
};

