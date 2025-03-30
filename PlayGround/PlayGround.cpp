#include "stdafx.h"
#include "PlayGround.h"
#include "IEvent.h"

HRESULT PlayGround::Init()
{
	GameNode::Init(true);

	Shantae* _shantae = new Shantae();
	OBJECTMANAGER->AddObject(ObjectType::Shantae, _shantae);

	Ground* _ground = new Ground();
	OBJECTMANAGER->AddObject(ObjectType::Ground, _ground);

	UI* _ui = new UI();
	OBJECTMANAGER->AddObject(ObjectType::UI, _ui);

	CAMERA->ChangeTarget(OBJECTMANAGER->FindObject(ObjectType::Shantae, L"Shantae"));
	CAMERA->SetCameraMode(CameraState::TARGET);
	////CAMERA->SetMapSize(Vector2(_bgImage->GetWidth(), WINSIZEY));
	

	//SCENEMANAGER->AddScene(L"IntroScene", new TestScene());
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
	SCENEMANAGER->Update();
	CAMERA->Update();

	EventManager::GetInstance()->Update();
}

void PlayGround::Render()
{	
	// 백버퍼 초기화
	D2DRenderer::GetInstance()->BeginRender(D2D1::ColorF::White);
	{
		SCENEMANAGER->Render();
		OBJECTMANAGER->Render();
	}
	D2DRenderer::GetInstance()->EndRender();
}
