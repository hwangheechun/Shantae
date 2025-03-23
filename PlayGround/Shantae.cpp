#include "stdafx.h"
#include "Shantae.h"
#include "Ground.h"
#include <string>

Shantae::Shantae()
	: _gauge(0.f)
{
	Init();
}

Shantae::~Shantae()
{
}

void Shantae::Init()
{
	_name = L"Shantae";
	_position = Vector2(WINSIZEX / 2 - 500, WINSIZEY / 2 + 100);
	_size = Vector2(70, 100);
	_rect = RectMakePivot(_position, _size, Pivot::Center);	// 히트박스
	_active = true;

	// 커스텀 변수들
	_direction = Vector2(1, 0);
	_gaugeRect = RectMakePivot(_position + Vector2(0, 60), Vector2(40.f, 10.f), Pivot::Center);

	_playerImage = IMAGEMANAGER->AddFrameImage(L"Shantae Idle", L"Resources/shantae_Idle.png", 16, 1);
	//_playerImage = IMAGEMANAGER->FindImage(L"Player Idle");
	//_playerImage = IMAGEMANAGER->AddImage(L"Player Idle", L"Resources/Idle.png");	// 일반 이미지

	_playerAnimation = new Animation();
	_playerAnimation->Init(_playerImage->GetWidth(), _playerImage->GetHeight(), _playerImage->GetFrameSize().x, _playerImage->GetFrameSize().y);
	_playerAnimation->SetPlayFrame(0, 15, false, true);
	_playerAnimation->SetFPS(10);	// 조정하면서 살펴보기
	_playerAnimation->Start();		// 이거 안 하면 시작 안 함

	//_ground = dynamic_cast<Ground*>(OBJECTMANAGER->FindObject(ObjectType::Ground, L"Ground"));
}

void Shantae::Release()
{
}

void Shantae::Update()
{
	_gravity += 2.5f;	//중력 가속

	if (KEYMANAGER->IsStayKeyDown(VK_LEFT))		//좌
	{
		if (_position.x > 0)
		{
			Move(Vector2(-35, 0), 10);
			
		}
		else _position.x = WINSIZEX;
	}
	if (KEYMANAGER->IsStayKeyDown(VK_RIGHT))	//우
	{
		if (_position.x < WINSIZEX)
		{
			Move(Vector2(35, 0), 10);
			
		}
		else _position.x = 0;
	}

	if (_position.y + _size.y / 2 >= OBJECTMANAGER->FindObject(ObjectType::Ground, L"Ground")->GetPosition().y)
	{
		_isOnGround = true;

		if (KEYMANAGER->IsOnceKeyDown(VK_SPACE))
		{
			_isOnGround = false;
			_gravity = -90.0f;
		}
	}

	if(!IsCollide(OBJECTMANAGER->FindObject(ObjectType::Ground, L"Ground")) && !_isOnGround)
		Move(Vector2(0.0f, _gravity), 10);
	// 0 -> 1 -> 2 / SetFPS를 통한 속도 반영
	_playerAnimation->FrameUpdate(TIMEMANAGER->GetElapsedTime());
}

void Shantae::Render()
{
	//_playerImage->FrameRender(_rect.GetCenter(), 0, 0);
	//_playerImage->Render(_rect.GetCenter());	// 일반 이미지
	//_D2DRenderer->FillRectangle(_rect, D2DRenderer::DefaultBrush::White);
	_D2DRenderer->DrawRectangle(_rect, D2DRenderer::DefaultBrush::Black, 2.0f);
	_playerImage->AniRender(_rect.GetCenter() + Vector2(0, -10), _playerAnimation, 1.2f);

	_D2DRenderer->RenderText(1060, 180, L"땅?" + to_wstring(_isOnGround) + L"점프?" + to_wstring(_isJumping), 15);
}

void Shantae::Move(Vector2 moveDirection, float speed)
{
	// 예시 1
	/*
	_position.x += moveDirection.x * speed * TIMEMANAGER->GetElapsedTime();
	_position.y += moveDirection.y * speed * TIMEMANAGER->GetElapsedTime();
	_rect = RectMakePivot(_position, _size, Pivot::Center);
	*/

	// 예시 2
	_position += moveDirection * speed * TIMEMANAGER->GetElapsedTime();	// == deltaTime
	_rect = RectMakePivot(_position, _size, Pivot::Center);
}

bool Shantae::IsCollide(GameObject* object)	//충돌했다면
{
	if (_position.x > object->GetPosition().x - object->GetSize().x / 2 && _position.x < object->GetPosition().x + object->GetSize().x / 2
		&& _position.y > object->GetPosition().y - object->GetSize().y / 2 && _position.y < object->GetPosition().y + object->GetSize().y / 2)
	{
		return true;
	}
	else return false;
}