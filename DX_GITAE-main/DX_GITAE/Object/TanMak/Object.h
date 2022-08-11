#pragma once
class Object
{
public:
	Object();
	Object(int hp, int attack);
	virtual ~Object();

	int GetHp() { return _hp; }
	int GetAttack() { return _attack; }
	void SetHp(int hp) { _hp = hp; }

	virtual void SetInfo(int hp, int attack);
	virtual void Attack(shared_ptr<Object> object) abstract;
	virtual void Damaged(int damage);

	virtual bool HpZero();
	bool _isActive;

protected:
	int _hp;
	int _attack;
};

