#pragma once
#include "GameObject.h"

class UI : public GameObject
{
public:
	UI();
	virtual ~UI();

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	//void Move(Vector2 moveDirection, float speed);
	//void MoveAngle(float angle, float speed);

	/*Vector2 _direction;
	Vector2 GetDirection() { return _direction; };*/

	Image* _gemsImage = nullptr;
	//Animation* _groundAnimation = nullptr;

};

