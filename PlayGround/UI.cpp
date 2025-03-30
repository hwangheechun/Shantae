#include "stdafx.h"
#include "UI.h"
#include <string>

UI::UI()
{
	Init();
}

UI::~UI()
{
}

void UI::Init()
{
	_name = L"UI";
	_position = Vector2(WINSIZEX - 100 , 50);
	_size = Vector2(200, 85);
	_rect = RectMakePivot(_position, _size, Pivot::Center);	// 히트박스
	_active = true;

	_gemsImage = IMAGEMANAGER->AddImage(L"UI_gems", L"Resources/UI_gems.png");
	/*_groundImage = IMAGEMANAGER->AddImage(L"Test", L"Resources/intro.png");
	_groundImage->SetSize(Vector2(100, 100));
	_groundImage->SetScale(0.1f);*/
}

void UI::Release()
{
}

void UI::Update()
{

}

void UI::Render()
{
	_gemsImage->Render(_position);
	_D2DRenderer->DrawRectangle(_rect, D2DRenderer::DefaultBrush::Blue, 3.0f);
	_D2DRenderer->RenderText(_position.x, _position.y, L"x는" + to_wstring(_position.x) + L"y는" + to_wstring(_position.y), 15);
}