#pragma once
class StartScene : public Scene
{
public:
	StartScene();
	virtual ~StartScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void Init() override;

	void NextScene();

private:
	shared_ptr<Button> _button;

};

