#include "Transform.h"
#include <cstdio>

Transform::Transform()
{
	position = { 0.0f, 0.0f };
	rotation = 0.0f;
	scale = 1.0f;
	center = { 0.0f, 0.0f };
}

void Transform::Update()
{

}

void Transform::LateUpdate()
{

}

Transform::~Transform()
{

}
