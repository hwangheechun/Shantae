#include "stdafx.h"
#include "Shantae.h"
#include "Ground.h"
#include <string>

Shantae::Shantae()
{
	Init();
}

Shantae::~Shantae()
{
}

void Shantae::Init()
{
	_name = L"Shantae";
	_position = Vector2(WINSIZEX / 2 - 6000, WINSIZEY / 2 + 300);
	_size = Vector2(60, 100);
	_rect = RectMakePivot(_position, _size, Pivot::Center);	// 히트박스
	_active = true;

	 IMAGEMANAGER->AddFrameImage(L"Shantae Idle_Right", L"Resources/shantae_idle2.png", 16, 1);
	 _playerImage = IMAGEMANAGER->AddFrameImage(L"Shantae Idle_Left", L"Resources/shantae_idle1.png", 16, 1);
	 IMAGEMANAGER->AddFrameImage(L"Shantae Run_Left", L"Resources/shantae_run1.png", 16, 1);
	 IMAGEMANAGER->AddFrameImage(L"Shantae Run_Right", L"Resources/shantae_run2.png", 16, 1);
	 IMAGEMANAGER->AddFrameImage(L"Shantae Jump_Left", L"Resources/shantae_jump1.png", 8, 1);
	 IMAGEMANAGER->AddFrameImage(L"Shantae Jump_Right", L"Resources/shantae_jump2.png", 8, 1);
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
	_playerAnimation->Init(_playerImage->GetWidth(), _playerImage->GetHeight(), _playerImage->GetFrameSize().x, _playerImage->GetFrameSize().y);

	if(!_isOnGround)
		Move(Vector2(0.0f, _gravity), 10);

	if (IsCollide(_rect.GetBottom(), OBJECTMANAGER->FindObject(ObjectType::Ground, L"Ground"), Pivot::Top))
	{
		_isOnGround = true;
		_rect.bottom = OBJECTMANAGER->FindObject(ObjectType::Ground, L"Ground")->GetPosition().y;
	}

	if (KEYMANAGER->IsStayKeyDown(VK_LEFT))		//좌
	{
		if (_isOnGround)
			_playerMode = ShantaeState::RUN_LEFT;
		else
			_playerMode = ShantaeState::JUMP_LEFT;
		_isRight = false;
		Move(Vector2(-35, 0), 10);

		if (KEYMANAGER->IsOnceKeyDown(VK_SPACE))	//점프
		{
			_isOnGround = false;
			_gravity = -90.0f;
		}
	}
	else if (KEYMANAGER->IsStayKeyDown(VK_RIGHT))	//우
	{
		if (_isOnGround)
			_playerMode = ShantaeState::RUN_RIGHT;
		else
			_playerMode = ShantaeState::JUMP_RIGHT;
		_isRight = true;
		Move(Vector2(35, 0), 10);

		if (KEYMANAGER->IsOnceKeyDown(VK_SPACE))	//점프
		{
			_isOnGround = false;
			_gravity = -90.0f;
		}
	}
	else
	{
		if (_isRight)
		{
			if(_isOnGround)
				_playerMode = ShantaeState::STAND_RIGHT;
			else
				_playerMode = ShantaeState::JUMP_RIGHT;
		}
		else
		{
			if (_isOnGround)
				_playerMode = ShantaeState::STAND_LEFT;
			else
				_playerMode = ShantaeState::JUMP_LEFT;
		}
		

		if (KEYMANAGER->IsOnceKeyDown(VK_SPACE))	//점프
		{
			_isOnGround = false;
			_gravity = -90.0f;
		}
	}

	//_rect = RectMakePivot(_position, _size, Pivot::Center);
	
	_playerAnimation->FrameUpdate(TIMEMANAGER->GetElapsedTime());

	switch (_playerMode)
	{
	case ShantaeState::STAND_LEFT:
		_playerImage = IMAGEMANAGER->FindImage(L"Shantae Idle_Left");
		_playerAnimation->SetPlayFrame(0, 15, false, true);
		break;
	case ShantaeState::STAND_RIGHT:
		_playerImage = IMAGEMANAGER->FindImage(L"Shantae Idle_Right");
		_playerAnimation->SetPlayFrame(0, 15, false, true);
		break;
	case ShantaeState::RUN_LEFT:
		_playerImage = IMAGEMANAGER->FindImage(L"Shantae Run_Left");
		_playerAnimation->SetPlayFrame(0, 15, false, true);
		break;
	case ShantaeState::RUN_RIGHT:
		_playerImage = IMAGEMANAGER->FindImage(L"Shantae Run_Right");
		_playerAnimation->SetPlayFrame(0, 15, false, true);
		break;
	case ShantaeState::JUMP_LEFT:
		_playerImage = IMAGEMANAGER->FindImage(L"Shantae Jump_Left");
		break;
	case ShantaeState::JUMP_RIGHT:
		_playerImage = IMAGEMANAGER->FindImage(L"Shantae Jump_Right");
		break;
	}
}

void Shantae::Render()
{
	//_playerImage->FrameRender(_rect.GetCenter(), 0, 0);
	//_playerImage->Render(_rect.GetCenter());	// 일반 이미지
	//_D2DRenderer->FillRectangle(_rect, D2DRenderer::DefaultBrush::White);
	_D2DRenderer->DrawRectangle(CAMERA->GetRelativeRect(_rect), D2DRenderer::DefaultBrush::Black, 2.0f);
	_D2DRenderer->DrawRectangle(_rect, D2DRenderer::DefaultBrush::Black, 5.0f);
	//_D2DRenderer->DrawRectangle(CAMERA->GetRelativeRect(_rect), D2DRenderer::DefaultBrush::Black, 2.0f);
	
	_D2DRenderer->RenderText(100, 100, to_wstring((int)_playerMode), 15);

	switch (_playerMode)
	{
	case ShantaeState::STAND_LEFT:
	case ShantaeState::STAND_RIGHT:
		_playerImage->AniRender(CAMERA->GetRelativeVector2(_position + Vector2(0, -30)), _playerAnimation, 3.0f);
		_playerAnimation->SetFPS(10);
		_D2DRenderer->RenderText(200, 100, L"서 있음", 15);
		break;
	case ShantaeState::RUN_LEFT :
	case ShantaeState::RUN_RIGHT:
		_playerImage->AniRender(CAMERA->GetRelativeVector2(_position + Vector2(0, -30)), _playerAnimation, 3.4f);
		_playerAnimation->SetFPS(15);
		_D2DRenderer->RenderText(200, 100, L"달림", 15);
		break;
	case ShantaeState::JUMP_LEFT:
	case ShantaeState::JUMP_RIGHT:
		_playerImage->AniRender(CAMERA->GetRelativeVector2(_position + Vector2(0, -30)), _playerAnimation, 2.0f);
		_playerAnimation->SetFPS(15);
		_D2DRenderer->RenderText(200, 100, L"점프", 15);
		break;

	}
}

void Shantae::Move(Vector2 moveDirection, float speed)
{
	_position += moveDirection * speed * TIMEMANAGER->GetElapsedTime();	// == deltaTime
	_rect = RectMakePivot(_position, _size, Pivot::Center);
}

bool Shantae::IsCollide(Vector2 contactPoint, GameObject* object, Pivot objectPivotType)	//충돌했다면
{
	switch (objectPivotType)
	{
	case Pivot::Center :
		if (contactPoint.x > object->GetPosition().x - object->GetSize().x / 2 && contactPoint.x < object->GetPosition().x + object->GetSize().x / 2
			&& contactPoint.y > object->GetPosition().y - object->GetSize().y / 2 && contactPoint.y < object->GetPosition().y + object->GetSize().y / 2)
		{
			return true;
		}
		else return false;
		break;
	case Pivot::Top :
		if (contactPoint.x > object->GetPosition().x - object->GetSize().x / 2 && contactPoint.x < object->GetPosition().x + object->GetSize().x / 2
			&& contactPoint.y > object->GetPosition().y && contactPoint.y < object->GetPosition().y + object->GetSize().y)
		{
			return true;
		}
		else return false;
		break;
	}
}