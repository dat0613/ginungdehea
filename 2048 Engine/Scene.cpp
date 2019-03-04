#include "Scene.h"

#define abs(a)  (((a)>0) ? (a):-(a))			//절대값 함수
#define EPSILON 0.0001f							//float형 자료형의 오차 범위
#define fsame(a, b) (((abs(a - b)) < EPSILON) ? (1) : (0))		//float형 두가지가 같은지 확인하는 매크로 함수. EPSILON 의 값에 따라 정확도가 달라짐

GameObject * Scene::GetGameObject(int num)
{
	std::list<GameObject *>::iterator iter;
	int checkNum;

	for (iter = UpdateList.begin(), checkNum = 0; iter != UpdateList.end(), checkNum++; iter++)
	{
		if (checkNum == num)
			return *iter;
	}
}

bool Scene::CheckAABBCollision(GameObject * o1, GameObject * o2)
{
	if (!CheckCircleCollision(o1, o2))
		return false;

	auto o1_position = o1->getPosition();
	auto o1_size = o1->getSpriteSize();

	auto o2_position = o2->getPosition();
	auto o2_size = o2->getSpriteSize();

	if ((o1_position.x < o2_position.x + o2_size.x) &&
		(o1_position.y < o2_position.y + o2_size.y) &&
		(o1_position.x + o1_size.x > o2_position.x) &&
		(o1_position.y + o1_size.y > o2_position.y))
		return true;

	return false;
}

bool Scene::CheckCircleCollision(GameObject * o1, GameObject * o2)
{

	auto o1_position = o1->GetCenter();
	auto o1_size = o1->getSpriteSize();

	auto o1_diagonal_len = D3DXVec2Length(&o1_size);	//대각선의 길이

	auto o2_position = o2->GetCenter();
	auto o2_size = o2->getSpriteSize();
	auto o2_diagonal_len = D3DXVec2Length(&o2_size);

	auto len = D3DXVec2Length(&(o1_position - o2_position));

	if (len < o1_diagonal_len * 0.5 + o2_diagonal_len * 0.5)
		return true;

	return false;
}

bool Scene::CheckOBBCollision(GameObject * o1, GameObject * o2)
{
	auto &vtxA = o1->GetVertices();
	auto &vtxB = o2->GetVertices();

	D3DXVECTOR2 o1_size = o1->getSpriteSize();
	float o1_len = D3DXVec2Length(&o1_size) * 0.5f;
	float theta = D3DXToRadian(o1->getDegree()) + atan2(o1_size.y, o1_size.x);
	D3DXVECTOR2 o1_pos = o1->getPosition();
	D3DXVECTOR2 o1_center = D3DXVECTOR2(o1_pos.x + cos(theta) * o1_len,o1_pos.y + sin(theta) * o1_len);

	D3DXVECTOR2 o2_size = o2->getSpriteSize();
	float o2_len = D3DXVec2Length(&o2_size) * 0.5f;
	theta = D3DXToRadian(o2->getDegree()) + atan2(o2_size.y, o2_size.x);
	D3DXVECTOR2 o2_pos = o2->getPosition();
	D3DXVECTOR2 o2_center = D3DXVECTOR2(o2_pos.x + cos(theta) * o2_len, o2_pos.y + sin(theta) * o2_len);

	D3DXVECTOR2 axis;
	D3DXVec2Normalize(&axis,&(vtxA[1] - vtxA[0]));
	float len = abs(D3DXVec2Dot(&axis, &(o1_center - o2_center)) * 2);
	float a_len = D3DXVec2Length(&(vtxA[1] - vtxA[0]));
	float b_len = abs(D3DXVec2Dot(&(vtxB[1] - vtxB[0]),&axis)) + abs(D3DXVec2Dot(&(vtxB[2] - vtxB[1]),&axis));
	if (len > a_len + b_len)
		return false;

	D3DXVec2Normalize(&axis, &(vtxA[2] - vtxA[1]));
	len = abs(D3DXVec2Dot(&axis, &(o1_center - o2_center)) * 2);
	a_len = D3DXVec2Length(&(vtxA[2] - vtxA[1]));
	b_len = abs(D3DXVec2Dot(&(vtxB[1] - vtxB[0]), &axis)) + abs(D3DXVec2Dot(&(vtxB[2] - vtxB[1]), &axis));
	if (len > a_len + b_len)
		return false;
	
	D3DXVec2Normalize(&axis, &(vtxB[1] - vtxB[0]));
	len = abs(D3DXVec2Dot(&axis, &(o1_center - o2_center)) * 2);
	a_len = D3DXVec2Length(&(vtxB[1] - vtxB[0]));
	b_len = abs(D3DXVec2Dot(&(vtxA[1] - vtxA[0]), &axis)) + abs(D3DXVec2Dot(&(vtxA[2] - vtxA[1]), &axis));
	if (len > a_len + b_len)
		return false;

	D3DXVec2Normalize(&axis, &(vtxB[2] - vtxB[1]));
	len = abs(D3DXVec2Dot(&axis, &(o1_center - o2_center)) * 2);
	a_len = D3DXVec2Length(&(vtxB[2] - vtxB[1]));
	b_len = abs(D3DXVec2Dot(&(vtxA[1] - vtxA[0]), &axis)) + abs(D3DXVec2Dot(&(vtxA[2] - vtxA[1]), &axis));
	if (len > a_len + b_len)
		return false;


	return true;
}

Scene::~Scene()
{
	Release();
}
 
void Scene::Update()
{
	std::list<GameObject *>::iterator iter;			//std::list 안에 있는 오브젝트를 가리키기 위한 변수

	iter = UpdateList.begin();						//list의 제일 앞을 가리킴

	while (iter != UpdateList.end())				//list의 제일 마지막 까지 순회할때 까지 루프
	{
		auto * nowObject = *iter;				//형변환(?)

		if(nowObject == NULL)						//만약 할당이 되어있지 않는 객체라면
			UpdateList.erase(iter++);				//list에서 제거하고 다음번으로 순회

		if (nowObject->enabled)						//만약 보통 상태의 오브젝트 라면
		{		
			nowObject->Update();					//오브젝트의 업데이트를 실행 하고 
			nowObject->UpdateZBuffer();
			++iter;									//다음번으로 순회

			if (nowObject->GetIsCollier())
			{
				if (nowObject->GetIsCanMove())
				{//충돌체크가 필요하며, 움직이는 물체
					MoveObjectList.push_back(nowObject);
				}
				else
				{//충돌체크가 필요하지만, 움직이지 않는 동적인 객체. 즉 이 객체들 끼리는 충돌 할 리가 없기 때문에 서로서로에 대한 판정을 할 필요가 없음.
					ColliderList.push_back(nowObject);
				}
			}

		}
		else
		{
			delete nowObject;						//파괴를 기다리는 오브젝트 라면 파괴 시키고 
			UpdateList.erase(iter++);				//다음번으로 순회
		}
	}
}

void Scene::LateUpdate()
{
	for (auto obj : UpdateList)
	{
		if (obj->enabled)
		{
			obj->LateUpdate();
		}
	}
}

void Scene::Collision()
{
	int ColliderListSize = ColliderList.size();
	int MoveObjectListSize = MoveObjectList.size();

	if (ColliderListSize == 0 && MoveObjectListSize == 0)
	{
		ColliderList.clear();
		MoveObjectList.clear();
		return;
	}

	//list보다 vector의 순회가 더 빠르기 때문에 list를 vector로 바꾸기 위한 std::vector
	std::vector<GameObject *> ColliderVector(ColliderListSize);			
	std::vector<GameObject *> MoveObjectVector(MoveObjectListSize);


	//list의 순회 속도 낭비를 최소화 하기 위해 한번의 list순회로 vector을 만듦
	int i = 0;							
	for (auto * object : ColliderList)
	{
		ColliderVector[i++] = object;
	}

	i = 0;
	for (auto * object : MoveObjectList)
	{
		MoveObjectVector[i++] = object;
		object->GetVertices();
	}

	//모든 객체들을 vector로 옮긴 다음 list를 전부 비움
	ColliderList.clear();
	MoveObjectList.clear();

	//충돌체크
	for (auto * MoveObject : MoveObjectVector)
	{
		for (auto * ColliderObject : ColliderVector)
		{
			if(MoveObject != ColliderObject)
			{ 
				if ((MoveObject->enabled && ColliderObject->enabled))
				{
					if (CheckCircleCollision(ColliderObject, MoveObject))	//더 효율적인 판정을 위해 비교적 빠른 원충돌을 먼저 해보고 고급 충돌검사를 함
					{
						if (CheckAABBCollision(ColliderObject, MoveObject))
						{
							ColliderObject->OnTriggerEnter(MoveObject);
							MoveObject->OnTriggerEnter(ColliderObject);
							break;
						}
					}
				}
			}
		}
	}

	for (auto * MoveObject_1 : MoveObjectVector)
	{
		for (auto * MoveObject_2 : MoveObjectVector)
		{
			if(MoveObject_1 != MoveObject_2)
			{ 
				if (!(MoveObject_1->getType() == MoveObject_2->getType() && MoveObject_1->getType() == GameObject::TYPE::Bullet))
				{
					if (MoveObject_1->enabled && MoveObject_2->enabled)
					{
						if (CheckCircleCollision(MoveObject_1, MoveObject_2))
						{
							if (CheckAABBCollision(MoveObject_1, MoveObject_2))
							{
								MoveObject_1->OnTriggerEnter(MoveObject_2);
								MoveObject_2->OnTriggerEnter(MoveObject_1);
								break;
							}
						}
					}
				}
			}
		}
	}

}

void Scene::Render()
{
	GraphicManager::GetInstance()->setRenderTargetList(&UpdateList);

	GraphicManager::GetInstance()->Render();
}

void Scene::Release()
{

}

void Scene::pushUpdateList(GameObject * obj)
{
	UpdateList.push_back(obj);
}
