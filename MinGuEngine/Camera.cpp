#include "Camera.h"
#include "Info.h"

GameObject* Camera::target = nullptr;
float Camera::scope = 0.35f;
float Camera::degree = 0.0f;
D3DXVECTOR2 Camera::position = D3DXVECTOR2(0.0f, 0.0f);
int Camera::shake = 0;
int Camera::radius = 0.0f;
D3DXMATRIX Camera::camMatrix = D3DXMATRIX();

void Camera::Init()
{
	//target = nullptr;
	//position = D3DXVECTOR2(0.0f, 0.0f);
}

void Camera::Update()
{
	if (radius > 0)
	{
		int degree = rand() % 360;
		float radian = D3DXToRadian(degree);
		
		auto pos = D3DXVECTOR2(cos(radian)*radius, sin(radian)*radius);
		position += pos;

		radius -= 10;
	}

	D3DXMATRIX CamRotation, PCamCenter, NCamCenter, CamScale, CamPosition;

	D3DXMatrixTranslation(&NCamCenter, -SCREENWIDTH * 0.5f, -SCREENHEIGHT * 0.5f, 0.0f);
	D3DXMatrixTranslation(&PCamCenter, SCREENWIDTH * 0.5f, SCREENHEIGHT * 0.5f, 0.0f);
	D3DXMatrixRotationZ(&CamRotation, D3DXToRadian(Camera::degree));
	D3DXMatrixScaling(&CamScale, scope, scope, 0.0f);

	camMatrix = NCamCenter * CamRotation * CamScale * PCamCenter;

	if (!target)
		return;

	auto targetPos = target->transform->position;
	targetPos.y = -1000.0f;
	auto sign = (target->flip) ? (-1) : 1;
	targetPos.x += 1000.0f * sign;
	auto diff = position - targetPos;
	diff *= -0.1f;

	position += diff;
	//position.x += 150.0f;
	//position.y = -730.0f;
}

void Camera::Shake(int power)
{
	radius = power;
}

void Camera::ZoomIn()
{
	scope += (scope * 0.05f);
}

void Camera::ZoomOut()
{
	scope -= (scope * 0.05f);
}
