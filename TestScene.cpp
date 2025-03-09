#include "stdafx.h"
#include "TestScene.h"

TestScene::~TestScene()
{
}

HRESULT TestScene::Init()
{
	// OBJECTMANAGER->AddObject(Ground~~~)

    return S_OK;
}

void TestScene::Release()
{
	// OBJECTMANAGER 지워 준다
}

void TestScene::Update()
{
	Scene::Update();

	// 조건이 달성이 되었다
	bool bTest = false;
	if (bTest) {
		SCENEMANAGER->ChangeScene(_nextScene);
	}
}

void TestScene::Render()
{
	Scene::Render();
}
