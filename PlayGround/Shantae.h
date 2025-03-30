#pragma once
#include "GameObject.h"

enum class ShantaeState : int
{
	STAND_LEFT,
	STAND_RIGHT,
	RUN_LEFT,
	RUN_RIGHT,
	JUMP_LEFT,
	JUMP_RIGHT,
};

class Shantae : public GameObject
{
public:
	Shantae();
	virtual ~Shantae();

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	void Move(Vector2 moveDirection, float speed);
	//void MoveAngle(float angle, float speed);

	//캐릭터 조작
	ShantaeState _playerMode = ShantaeState::STAND_RIGHT;
	Image* _playerImage = nullptr;
	Animation* _playerAnimation = nullptr;
	bool _isRight = false;

	//충돌 관련
	bool IsCollide(Vector2 contactPoint,GameObject* object, Pivot objectPivotType);

	//중력 관련
	float _gravity = 0.f;
	bool _isOnGround = false;
	bool _isJumping = false;
};

