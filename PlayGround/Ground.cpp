#include "stdafx.h"
#include "Ground.h"
#include <string>

Ground::Ground()
{
	Init();
}

Ground::~Ground()
{
}

void Ground::Init()
{
	_name = L"Ground";
	_position = Vector2(WINSIZEX / 2, WINSIZEY / 2 + 425);
	_size = Vector2(13000, 50);
	_rect = RectMakePivot(_position, _size, Pivot::Top);	// 히트박스
	_active = true;

	_groundImage = IMAGEMANAGER->AddImage(L"Test", L"Resources/intro.png");
	_groundImage->SetSize(Vector2(100, 100));
	_groundImage->SetScale(0.1f);
}

void Ground::Release()
{
}

void Ground::Update()
{

}

void Ground::Render()
{
	_groundImage->Render(CAMERA->GetRelativeVector2(_position + Vector2(0, -205)));
	_D2DRenderer->DrawRectangle(CAMERA->GetRelativeRect(_rect), D2DRenderer::DefaultBrush::Red, 3.0f);
	_D2DRenderer->RenderText(_position.x, _position.y, L"x는" + to_wstring(_position.x) + L"y는" +to_wstring(_position.y), 15);
}