#include "framework.h"
#include "StartScene.h"

StartScene::StartScene()
{
	_button = make_shared<Button>();
	_button->SetPosition(CENTER);
	_button->SetScale(Vector2(0.1f, 0.1f));
	_button->SetEvent(std::bind(&StartScene::NextScene, this));
}

StartScene::~StartScene()
{

}

void StartScene::Update()
{
	_button->Update();
}

void StartScene::Render()
{
	
}

void StartScene::PostRender()
{
	_button->PostRender();
}

void StartScene::Init()
{
	_button->SetPosition(CENTER);
}

void StartScene::NextScene()
{
	SCENE->SetCurSence("TanMak");
}
