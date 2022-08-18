#include "framework.h"
#include "Button.h"

Button::Button()
{
	_quad = make_shared<Quad>(L"Resource/UI/Button.png", L"Shader/TextureVertexShader.hlsl", L"Shader/ButtonPixelShader.hlsl");
	_collider = make_shared<RectCollider>(_quad->GetHalfSize());
	_collider->SetParent(_quad->GetTransform());

	_buttonBuffer = make_shared<ButtonBuffer>();
	_buttonBuffer->_data._state = 0;
	_buttonBuffer->_data._hover = 0.1f;
	_buttonBuffer->_data._click = 0.3f;
}

Button::~Button()
{
}

void Button::Update()
{
	_quad->Update();
	_collider->Update();

	if (_collider->IsCollision(MOUSE_POS))
	{
		_collider->SetColorRed();
		_state = Button::State::HOVER;
		_buttonBuffer->_data._state = static_cast<int>(Button::State::HOVER);
		if (KEY_PRESS(VK_LBUTTON))
		{
			_state = Button::State::CLICK;
			_buttonBuffer->_data._state = static_cast<int>(Button::State::CLICK);
		}

		if (KEY_UP(VK_LBUTTON))
		{
			if (_callBack != nullptr)
				_callBack();

			if (_callBackint != nullptr)
				_callBackint(10);
		}

	}
	else
	{
		_collider->SetColorGreen();
		_state = Button::State::NONE;
		_buttonBuffer->_data._state = static_cast<int>(Button::State::NONE);
	}
}

void Button::PostRender()
{
	_quad->Render();
	_collider->Render();

	{
		Vector2 offset;

		float sizeX = _quad->GetHalfSize().x;
		float sizeY = _quad->GetHalfSize().y;
		offset.x = sizeX * 0.5f;
		offset.y = sizeY * 0.5f;

		RECT rect;
		rect.left = _buttonPos.x - sizeX + offset.x;
		rect.top = (WIN_HEIGHT - _buttonPos.y) - sizeY + offset.y;
		rect.right = _buttonPos.x + sizeX + offset.x;
		rect.bottom = (WIN_HEIGHT - _buttonPos.y) + sizeY + offset.y;

		DirectWrite::GetInstance()->RenderText(StrToWstr(_text), rect);
	}

	Vector2 temp = Camera::GetInstance()->GetMouseWorldPos();
	ImGui::SliderFloat("MouseX", &temp.x, -2000, 3000);
	ImGui::SliderFloat("MouseY", &temp.y, -2000, 3000);

	_buttonBuffer->SetPSBuffer(1);
}

void Button::SetPosition(Vector2 pos)
{
	_quad->GetTransform()->GetPos() = pos;
	_buttonPos = pos;
}

void Button::SetScale(Vector2 scale)
{
	_quad->GetTransform()->GetScale() = scale;
}

void Button::SetText(string text)
{
	_text = text;
}
