#include "Cube.h"

#include "Info.h"

Cube::Cube()
{
	animation->SetType(Animation::TYPE::Cube);
	transform->position = { SCREENWIDTH * 0.5f, SCREENHEIGHT * 0.5f };
}

void Cube::Update()
{
	transform->rotation += 2.0f;
}

Cube::~Cube()
{

}