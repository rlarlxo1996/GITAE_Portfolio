#include "framework.h"
#include "TanMakScene.h"

TanMakScene::TanMakScene()
{
	_backGround = make_shared<Quad>(L"Resource/Carina_Nebula.png");
	_backGround->GetTransform()->GetPos().x += _backGround->GetHalfSize().x;
	_backGround->GetTransform()->GetPos().y += _backGround->GetHalfSize().y;

	_player = make_shared<Player>();
	_player->GetTransform()->GetPos() = { CENTER.x , CENTER.y - 250 };

	//_enemy = make_shared<Enemy>();



	for (int i = 0; i < 10; i++)
	{
		shared_ptr<Enemy> enemy = make_shared<Enemy>();

		enemy->GetTransform()->GetPos() = { CENTER.x * i / 2 , CENTER.y };

		_enemies.emplace_back(enemy);
	}
	
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

	//_enemy->Update();

	PlayerAttack();

	EnemyAttack();

	MoveRestrict();

	if (_player->_isActive == false)
	{
		PrevScene();
	}

	for (auto& enemy : _enemies)
	{
		enemy->Update();
	}
}

void TanMakScene::Render()
{
	_backGround->Render();

	_player->Render();

	//_enemy->Render();

	for (auto& enemy : _enemies)
	{
		enemy->Render();
	}
}

void TanMakScene::PostRender()
{
	//ImGui::Text("Player Info");
	//ImGui::Text("P.X : %0.1f, P.Y : %0.1f", _player->GetTransform()->GetPos().x, _player->GetTransform()->GetPos().y);
}

void TanMakScene::Init()
{
	_player->Init();
	_player->_isActive = true;
	_player->GetCollider()->_isActive = true;
	_player->SetHp(5);
	
	Camera::GetInstance()->GetTransform()->GetPos().y = 0;
}

void TanMakScene::MoveRestrict()
{
	if (_player->GetTransform()->GetPos().x <= Camera::GetInstance()->GetMoveTransform()->GetPos().x + 45.0f)
		_player->GetTransform()->GetPos().x = Camera::GetInstance()->GetMoveTransform()->GetPos().x + 45.0f;

	if (_player->GetTransform()->GetPos().x >= WIN_WIDTH - 50)
		_player->GetTransform()->GetPos().x = WIN_WIDTH - 50;

	if (_player->GetTransform()->GetPos().y <= Camera::GetInstance()->GetMoveTransform()->GetPos().y + 25.0f)
		_player->GetTransform()->GetPos().y = Camera::GetInstance()->GetMoveTransform()->GetPos().y + 25.0f;

	if (_player->GetTransform()->GetPos().y >= _backGround->GetSize().y)
		_player->GetTransform()->GetPos().y = _backGround->GetSize().y;

}

void TanMakScene::PlayerAttack()
{
	for (int i = 0; i < 10; i++)
	{
		for (auto& bullet : _player->GetBullet())
		{
			if (bullet->GetCollider()->IsCollision(_enemies[i]->GetCollider()) && bullet->_isActive == true)
			{
				bullet->_isActive = false;
				_enemies[i]->Damaged(_player->GetAttack());

				if (_enemies[i]->_isActive == false)
				{
					_enemies[i]->GetCollider()->_isActive = false;
				}
				break;
			}
		}
	}
}

void TanMakScene::EnemyAttack()
{
	for (int i = 0; i < 10; i++)
	{
		for (auto& bullet : _enemies[i]->GetBullet())
		{
			if (bullet->GetCollider()->IsCollision(_player->GetCollider()) && bullet->_isActive == true)
			{
				bullet->_isActive = false;
				_player->Damaged(_player->GetAttack());

				if (_player->_isActive == false)
				{
					_player->GetCollider()->_isActive = false;
				}
				break;
			}
		}
	}
}

void TanMakScene::PrevScene()
{
	SCENE->SetCurSence("Lobby");
}
