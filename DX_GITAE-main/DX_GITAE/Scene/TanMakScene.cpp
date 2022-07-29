#include "framework.h"
#include "TanMakScene.h"

TanMakScene::TanMakScene()
{
	_backGround = make_shared<Quad>(L"Resource/Carina_Nebula.png");
	_backGround->GetTransform()->GetPos().x += _backGround->GetHalfSize().x;
	_backGround->GetTransform()->GetPos().y += _backGround->GetHalfSize().y;

	_player = make_shared<Player>();
	_player->SetPosition({ CENTER.x, CENTER.y});
	
	_playerFollow = make_shared<Transform>();
	_playerFollow->GetPos() = _player->GetTransform()->GetPos();

	Camera::GetInstance()->SetTarget(_playerFollow);
	Camera::GetInstance()->SetLeftBottom({ 0, 0 });
	Camera::GetInstance()->SetRightTop({ _backGround->GetSize().x, _backGround->GetSize().y });
}

TanMakScene::~TanMakScene()
{
}

void TanMakScene::Update()
{
	_backGround->Update();

	_player->Update();

	float distance = _player->GetTransform()->GetPos().Distance(_playerFollow->GetPos());

	if (distance >= 10.0f)
		_playerFollow->GetPos() = LERP(_playerFollow->GetPos(), _player->GetTransform()->GetPos(), DELTA_TIME * 5);
}

void TanMakScene::Render()
{
	_backGround->Render();

	_player->Render();
}

void TanMakScene::PostRender()
{

}
