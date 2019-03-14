#include "RigidBody2D.h"
#include "GameObject.h"

RigidBody2D::RigidBody2D()
{
	this->bodyType = BodyType::Dynamic;
	velocity = D3DXVECTOR2(0.0f, 0.0f);
	gravity = 0.0f;
	gravityAccel = 1.1f;
	gravityScale = 0.1f;
}

RigidBody2D::~RigidBody2D()
{

}

void RigidBody2D::Update()
{
	// Static �� �������� ����
	if (bodyType == BodyType::Static)
		return;


	// Dynamic �� �߷��� ������ ����
	if (bodyType == BodyType::Dynamic)
	{
		velocity.y += gravity;
		gravity += gravityScale;
		gravityScale *= gravityAccel;
		printf("%f\n", gravity);
	}
	GetGameObject()->transform->position += velocity;
}
