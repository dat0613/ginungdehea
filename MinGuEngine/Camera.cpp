#include "Camera.h"

GameObject* Camera::target = nullptr;
float Camera::scope = 1.0f;
float Camera::degree = 0.0f;
D3DXVECTOR2 Camera::position = D3DXVECTOR2(0.0f, 0.0f);

void Camera::Init()
{
	//target = nullptr;
	//position = D3DXVECTOR2(0.0f, 0.0f);
}

void Camera::Update()
{
	if (!target)
		return;

	auto diff = position - target->transform->position;
	diff *= -0.1f;

	position += diff;
}