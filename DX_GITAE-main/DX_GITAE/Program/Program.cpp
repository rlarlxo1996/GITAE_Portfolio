#include "framework.h"
#include "Program.h"

#include "../Scene/TanMakScene.h"

Program::Program()
{
	_scene = make_shared<TanMakScene>();
}

Program::~Program()
{
}

void Program::Update()
{
	_scene->Update();
	EffectManager::GetInstance()->Update();
	Camera::GetInstance()->Update();
}

void Program::Render()
{
	Device::GetInstance()->Clear();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	Camera::GetInstance()->SetProjectionBuffer(WIN_WIDTH, WIN_HEIGHT);
	Camera::GetInstance()->SetViewPort(WIN_WIDTH, WIN_HEIGHT);

	ALPHA_STATE->SetState();

	_scene->PreRender();

	_scene->Render();
	EffectManager::GetInstance()->Render();

	wstring fps = L"FPS : " + to_wstring((int)Timer::GetInstance()->GetFPS());
	RECT rect = { 0,0,100,100 };

	DirectWrite::GetInstance()->GetDC()->BeginDraw();
	DirectWrite::GetInstance()->RenderText(fps, rect);

	_scene->PostRender();
	Camera::GetInstance()->PostRender();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	DirectWrite::GetInstance()->GetDC()->EndDraw();
	Device::GetInstance()->Present();
}
