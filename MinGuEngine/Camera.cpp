#include "Camera.h"

GameObject* Camera::target = nullptr;
float Camera::scope = 0.1f;
float Camera::degree = 0.0f;
D3DXVECTOR2 Camera::position = D3DXVECTOR2(0.0f, 0.0f);
int Camera::shake = 0;
int Camera::radius = 0.0f;

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

	if (radius > 0)
	{
		int degree = rand() % 360;
		float radian = D3DXToRadian(degree);
		
		auto pos = D3DXVECTOR2(cos(radian)*radius, sin(radian)*radius);
		position += pos;

		radius -= 10;
	}
}

void Camera::Shake(int power)
{
	radius = power;
}
