#include "framework.h"
#include "TanMakScene.h"

TanMakScene::TanMakScene()
{
	_backGround = make_shared<Quad>(L"Resource/Carina_Nebula.png");
	_backGround->GetTransform()->GetPos().x += _backGround->GetHalfSize().x;
	_backGround->GetTransform()->GetPos().y += _backGround->GetHalfSize().y;

	_player = make_shared<Player>();

	_enemy = make_shared<Enemy>();
	
	_playerFollow = make_shared<Transform>();
	_playerFollow->GetPos() = _player->GetTransform()->GetPos();

	Camera::GetInstance()->SetTarget(_playerFollow);
	Camera::GetInstance()->SetLeftBottom({ 0, 0 });
	Camera::GetInstance()->SetRightTop({ _backGround->GetSize().x, _backGround->GetSize().y });

	SOUND->Add("bgm", "Resource/Sound/drumloop.wav", true);
	SOUND->Play("bgm");
}

TanMakScene::~TanMakScene()
{
}

void TanMakScene::Update()
{
	_backGround->Update();

	_player->Update();

	_enemy->Update();

	float distance = _player->GetTransform()->GetPos().Distance(_playerFollow->GetPos());

	if (distance >= 10.0f)
		_playerFollow->GetPos() = LERP(_playerFollow->GetPos(), _player->GetTransform()->GetPos(), DELTA_TIME * 5);

	for (auto& bullet : _player->GetBullet())
	{
		if (bullet->GetCollider()->IsCollision(_enemy->GetCollider()) && bullet->_isActive == true)
		{
			bullet->_isActive = false;
			_enemy->Damaged(_player->GetAttack());
			break;
		}
		else
		{
		}
	}
}

void TanMakScene::Render()
{
	_backGround->Render();

	_player->Render();

	_enemy->Render();
}

void TanMakScene::PostRender()
{

}
