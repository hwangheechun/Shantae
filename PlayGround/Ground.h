#pragma once
#include "GameObject.h"

class Ground : public GameObject
{
public:
	Ground();
	virtual ~Ground();

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	//void Move(Vector2 moveDirection, float speed);
	//void MoveAngle(float angle, float speed);

	/*Vector2 _direction;
	Vector2 GetDirection() { return _direction; };*/

	Image* _groundImage = nullptr;
	//Animation* _groundAnimation = nullptr;
};

