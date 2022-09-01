#pragma once
class TanMakScene : public Scene
{
public:
	TanMakScene();
	virtual ~TanMakScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void Init() override;

	void MoveRestrict();
	void PlayerAttack();
	void EnemyAttack();
	void PrevScene();

private:
	shared_ptr<Quad> _backGround;

	shared_ptr<Player> _player;

	shared_ptr<Transform> _cameraFollow;

	shared_ptr<Enemy> _enemy;

	vector<shared_ptr<Enemy>> _enemies;

	int enemyCount = 4;
};

