#include "stdafx.h"
#include "Camera.h"
#include "GameObject.h"

Camera::Camera()
	: _position(0.f, 0.f), _mapSize(Vector2(WINSIZEX , WINSIZEY))
{
}

void Camera::Update()
{
	switch (_state)
	{
	case CameraState::TARGET:
		MoveToTarget();
		break;
	case CameraState::TARGET_LERP:
		MoveToTarget_Lerp();
		break;
	case CameraState::END:
		break;
	default:
		break;
	}
}

void Camera::ChangeTarget(GameObject* object)
{
	_target = object;
}

void Camera::MoveToTarget()
{
	if (_target == nullptr)
		return;

	_position = _target->GetPosition() + Vector2(0,-250);

	UpdateRect();
	//CheckRect();
}

void Camera::MoveToTarget_Lerp()
{
	if (_target == nullptr)
		return;

	float lerpFactor = 0.1f;	// �ε巯�� �̵� ����
	_position = Lerp(_position, _target->GetPosition(), lerpFactor);

	UpdateRect();
	CheckRect();
}

Vector2 Camera::GetRelativeVector2(Vector2 vector)
{
	return vector - Vector2(_rc.left, _rc.top);
}

FloatRect Camera::GetRelativeRect(FloatRect _rect)
{
	FloatRect relativeRect;

	relativeRect.top = _rect.top - _rc.top;
	relativeRect.left = _rect.left - _rc.left;
	relativeRect.right = _rect.right - _rc.left;
	relativeRect.bottom = _rect.bottom - _rc.top;

	return relativeRect;
}

void Camera::UpdateRect()
{
	_rc = RectMakePivot(_position, Vector2{ WINSIZEX, WINSIZEY }, Pivot::Center);
}

void Camera::CheckRect()
{
	Vector2 newPos = _position;

	if (_rc.left < 0.f)
		newPos.x -= _rc.left;
	if (_rc.right > _mapSize.x)
		newPos.x -= _rc.right - _mapSize.x;

	/*if (_rc.top < 0.f)
		newPos.y -= _rc.top;*/
	if (_rc.bottom > _mapSize.y)
		newPos.y -= _rc.bottom - _mapSize.y;

	if (newPos != _position) {
		_position = newPos;
		UpdateRect();
	}
}

Vector2 Camera::Lerp(Vector2 start, Vector2 end, float t)
{
	return start + (end - start) * t;
}
