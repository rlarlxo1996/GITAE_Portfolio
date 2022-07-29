#include "framework.h"
#include "Gun.h"

Gun::Gun()
{
	_quad = make_shared<Quad>(L"Resource/Gun.png");
	_quad->GetTransform()->GetScale() = { 0.3f,0.3f };
}

Gun::~Gun()
{
}

void Gun::Update()
{
	_quad->Update();
}

void Gun::Render()
{
	_quad->Render();
}
