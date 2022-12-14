#include "framework.h"
#include "Program.h"

Program::Program()
{
	SCENE->SetCurSence("Lobby");
}

Program::~Program()
{
}

void Program::Update()
{
	SCENE->Update();
	EffectManager::GetInstance()->Update();
	Camera::GetInstance()->Update();
	Audio::GetInstance()->Update();
}

void Program::Render()
{
	Camera::GetInstance()->SetProjectionBuffer(WIN_WIDTH, WIN_HEIGHT);
	Camera::GetInstance()->SetCameraWorldBuffer();

	SCENE->PreRender();

	Device::GetInstance()->SetRTV();
	Device::GetInstance()->Clear();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	Camera::GetInstance()->SetViewPort(WIN_WIDTH, WIN_HEIGHT);

	ALPHA_STATE->SetState();

	SCENE->Render();
	EffectManager::GetInstance()->Render();

	wstring fps = L"FPS : " + to_wstring((int)Timer::GetInstance()->GetFPS());
	RECT rect = { 0,0,100,100 };

	DirectWrite::GetInstance()->GetDC()->BeginDraw();
	DirectWrite::GetInstance()->RenderText(fps, rect);

	Camera::GetInstance()->SetUiCameraBuffer();
	SCENE->PostRender();
	Camera::GetInstance()->PostRender();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	DirectWrite::GetInstance()->GetDC()->EndDraw();
	Device::GetInstance()->Present();
}
