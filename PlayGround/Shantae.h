#pragma once
#include "GameObject.h"

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

	Vector2 _direction;
	Vector2 GetDirection() { return _direction; };

	float _gauge;
	FloatRect _gaugeRect;

	Image* _playerImage = nullptr;
	Animation* _playerAnimation = nullptr;

	//충돌 관련
	bool IsCollide(GameObject* Object);

	//중력 관련
	float _gravity = 0.f;
	bool _isOnGround = false;
	bool _isJumping = false;
};

