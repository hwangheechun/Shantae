#include "stdafx.h"
#include "PlayGround.h"
#include "IEvent.h"
#include "Bullet.h"
#include "TestScene.h"

HRESULT PlayGround::Init()
{
	GameNode::Init(true);

	Player* player = new Player();

	OBJECTMANAGER->AddObject(ObjectType::Player, player);

	SCENEMANAGER->AddScene(L"TestScene", new TestScene());
	/*
	SCENEMANAGER->AddScene(L"TestScene2", new TestScene2());
	SCENEMANAGER->AddScene(L"TestScene3", new TestScene3());
	SCENEMANAGER->AddScene(L"TestScene4", new TestScene4());
	SCENEMANAGER->AddScene(L"TestScene5", new TestScene5());
	*/

	return S_OK;
}

void PlayGround::Release()
{
	OBJECTMANAGER->Release();
}

void PlayGround::Update()
{
	GameNode::Update();

	OBJECTMANAGER->Update();

	EventManager::GetInstance()->Update();
}

void PlayGround::Render()
{	
	// 백버퍼 초기화
	D2DRenderer::GetInstance()->BeginRender(D2D1::ColorF::White);
	{
		OBJECTMANAGER->Render();
	}
	D2DRenderer::GetInstance()->EndRender();
}
