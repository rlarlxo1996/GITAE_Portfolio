#pragma once
class TanMakScene : public Scene
{
public:
	TanMakScene();
	virtual ~TanMakScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	shared_ptr<Quad> _backGround;

	shared_ptr<Player> _player;
	shared_ptr<Transform> _playerFollow;

	shared_ptr<Enemy> _enemy;
};

