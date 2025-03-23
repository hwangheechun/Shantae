#pragma once
#include "GameNode.h"

class Scene : public GameNode
{
	// Ÿ�ϸ� & ����ȭ/������ȭ
public:
	Scene();
	virtual ~Scene() override;

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

protected:
	wstring _nextScene;
};

class IntroScene : public Scene
{
public:
	virtual ~IntroScene() override;

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

private:
	Image* _introImage;
};

//class MainScene : public Scene
//{
//public:
//	virtual ~MainScene() override;
//
//	HRESULT Init() override;
//	void Release() override;
//	void Update() override;
//	void Render() override;
//
//private:
//	Image* _bgImage;
//};
//
//class AfterDeadScene : public Scene
//{
//public:
//	virtual ~AfterDeadScene() override;
//
//	HRESULT Init() override;
//	void Release() override;
//	void Update() override;
//	void Render() override;
//private:
//	Image* _bgImage;
//};


