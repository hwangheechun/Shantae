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
	_position = Vector2(WINSIZEX / 2, WINSIZEY / 2 + 225);
	_size = Vector2(WINSIZEX + 50, 50);
	_rect = RectMakePivot(_position, _size, Pivot::Top);	// 히트박스
	_active = true;

	_groundImage = IMAGEMANAGER->AddImage(L"Test", L"Resources/test_ground.png");
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
	_groundImage->Render(_rect.GetBottom() + Vector2(0,60));
	_D2DRenderer->DrawRectangle(_rect, D2DRenderer::DefaultBrush::Black, 2.0f);
}