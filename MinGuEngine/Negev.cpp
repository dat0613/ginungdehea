#include "Negev.h"
#include "Controller.h"

Negev::Negev()
{
	//AddComponent<Controller>();
	animation->SetType(Animation::Negev);
	boxcollider2d->SetColliderSize(252, 352);
}

Negev::~Negev()
{

}

void Negev::Update()
{

}
