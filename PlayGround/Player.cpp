#include "stdafx.h"
#include "Player.h"

Player::Player()
	: _gauge(0.f)
{
	Init();
}

Player::~Player()
{
}

void Player::Init()
{
	_name = L"Player";
	_position = Vector2(WINSIZEX / 2, WINSIZEY / 2);
	_size = Vector2(100, 100);
	_rect = RectMakePivot(_position, _size, Pivot::Center);	// 히트박스
	_active = true;

	// 커스텀 변수들
	_direction = Vector2(1, 0);
	_gaugeRect = RectMakePivot(_position + Vector2(0, 60), Vector2(40.f, 10.f), Pivot::Center);

	_playerImage = IMAGEMANAGER->AddFrameImage(L"Player Idle", L"Resources/idle.png", 11, 1);
	//_playerImage = IMAGEMANAGER->FindImage(L"Player Idle");
	//_playerImage = IMAGEMANAGER->AddImage(L"Player Idle", L"Resources/Idle.png");	// 일반 이미지
	
	_playerAnimation = new Animation();
	_playerAnimation->Init(_playerImage->GetWidth(), _playerImage->GetHeight(), _playerImage->GetFrameSize().x, _playerImage->GetFrameSize().y);
	_playerAnimation->SetPlayFrame(0, 10, false, true);
	_playerAnimation->SetFPS(10);	// 조정하면서 살펴보기
	_playerAnimation->Start();		// 이거 안 하면 시작 안 함
}

void Player::Release()
{
}

void Player::Update()
{
	// 0 -> 1 -> 2 / SetFPS를 통한 속도 반영
	_playerAnimation->FrameUpdate(TIMEMANAGER->GetElapsedTime());
}

void Player::Render()
{
	_playerImage->AniRender(_rect.GetCenter(), _playerAnimation, 2.0f);
	//_playerImage->FrameRender(_rect.GetCenter(), 0, 0);
	//_playerImage->Render(_rect.GetCenter());	// 일반 이미지
}

void Player::Move(Vector2 moveDirection, float speed)
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