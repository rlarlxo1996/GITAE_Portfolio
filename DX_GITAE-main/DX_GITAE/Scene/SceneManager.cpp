#include "framework.h"
#include "SceneManager.h"

#include "../Scene/GameScene/TanMakScene.h"
#include "../Scene/GameScene/StartScene.h"

SceneManager* SceneManager::_instance = nullptr;

SceneManager::SceneManager()
{
	_sceneTable["Lobby"] = make_shared<StartScene>();
	_sceneTable["TanMak"] = make_shared<TanMakScene>();

	SetCurSence("Lobby");
}

SceneManager::~SceneManager()
{
}

void SceneManager::Update()
{
	if (_curScene.expired())
		return;

	_curScene.lock()->Update();
}

void SceneManager::Render()
{
	if (_curScene.expired())
		return;

	_curScene.lock()->Render();
}

void SceneManager::PreRender()
{
	if (_curScene.expired())
		return;

	_curScene.lock()->PreRender();
}

void SceneManager::PostRender()
{
	if (_curScene.expired())
		return;

	_curScene.lock()->PostRender();
}

void SceneManager::SetCurSence(string name)
{
	if (_sceneTable.count(name) == 0)
		return;

	_curScene = _sceneTable[name];
	_curScene.lock()->Init();
}