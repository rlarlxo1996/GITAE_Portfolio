#include "framework.h"
#include "Object.h"

Object::Object()
: _hp(0)
, _attack(0)
, _isActive(true)
{
}

Object::Object(int hp, int attack)
: _hp(hp)
, _attack(attack)
, _isActive(true)
{
}

Object::~Object()
{
}

void Object::SetInfo(int hp, int attack)
{
	_hp = hp;
	_attack = attack;
}

void Object::Damaged(int damage)
{
	if (_isActive == false)
		return;

	_hp -= damage;

	if (_hp <= 0)
	{
		_hp = 0;
		_isActive = false;
	}
}

bool Object::HpZero()
{
	if (_hp <= 0) { return false; }
	else { return true; }
}
