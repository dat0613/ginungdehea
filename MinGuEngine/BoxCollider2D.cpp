#include "BoxCollider2D.h"

BoxCollider2D::BoxCollider2D()
{
	size = D3DXVECTOR2(0.0f, 0.0f);
	radius = 0.0f;
}

BoxCollider2D::~BoxCollider2D()
{

}

void BoxCollider2D::Update()
{

}

void BoxCollider2D::SetColliderSize(D3DXVECTOR2 size)
{
	this->size = size;
	this->radius = D3DXVec2Length(&size) * 0.5f;
}

void BoxCollider2D::SetColliderSize(float x, float y)
{
	SetColliderSize({ x,y });
}