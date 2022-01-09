#include "Physics.hpp"

bool Physics::Init()
{
	return true;
}

void Physics::GetObjManager(ObjectManager* p_objmanager) 
{ 
	m_objectmanager = p_objmanager; 
	m_objMap = m_objectmanager->GetObjectMapPointer();
}


bool Physics::Update(float dt)
{
	if (m_objectmanager == nullptr) return true;
	m_duration = dt;
	for (std::map<std::string, Object*>::iterator i = m_objMap->begin();
		i != m_objMap->end(); ++i)
	{
		if (i->second->GetRigidbody() == nullptr) continue;
		std::map<std::string, Object*>::iterator j = i;
		j++;
		for (; j != m_objMap->end(); ++j)
		{
			if (i->first == j->first)
				break;
			if (j->second->GetRigidbody() == nullptr) continue;
			if (i->second->m_objectType == ObjectType::antienemy && j->second->m_objectType == ObjectType::antienemy)
				continue;

			if (i->second->move_type == MoveType::stay&& j->second->move_type == MoveType::stay)
				continue;

			bool isCollide = m_collisionChecker.CollisionCheck(i->second, j->second);
			if (i->second->IsGhost || j->second->IsGhost)
			{
				i->second->IsCollide = true; j->second->IsCollide = true;
				isCollide = false;
			}

			if (isCollide)
			{
				i->second->CollideWithType(j->second->m_objectType);
				j->second->CollideWithType(i->second->m_objectType);
				//if (i->second->IsDelete) isCollide = false; //튕겨나가기 전에 삭제하면 안됨..
				//if (j->second->IsDelete) isCollide = false;
			}
			if (isCollide) //If these are not ghost
				isCollide = resolveVelocity(i->second, j->second);
			if (isCollide) //After resolve, still colliding
			{
				if (i->second->GetMesh().mesh_polygon_type == MeshPolygonType::Box &&
					j->second->GetMesh().mesh_polygon_type == MeshPolygonType::Box)
					resolveInterAABB(i->second, j->second);
				else if (i->second->GetMesh().mesh_polygon_type == MeshPolygonType::Circle &&
					j->second->GetMesh().mesh_polygon_type == MeshPolygonType::Circle)
					resolveInterpenetration(i->second, j->second);
				else
					resolveInterAABB(i->second, j->second);

				i->second->IsCollide = true;
				j->second->IsCollide = true;
			}
		}
	}

	for (std::map<std::string, Object*>::iterator i = m_objMap->begin();
		i != m_objMap->end(); ++i)
	{
		if (i->second->GetRigidbody() == nullptr) continue;
		if (i->second->IsDelete) continue;
 		integrate(i->second, dt);
	}
	return true;
}


void Physics::integrate(Object* p_obj, float dt)
{
	vector2 velocity = p_obj->GetVelocity();
	vector2 resultAcc = p_obj->GetAcceleartion() + p_obj->force_accumlator * (1 / p_obj->GetRigidbody()->GetMass());
	velocity += resultAcc * dt;

	if (!(p_obj->GetRigidbody()->IsSliding()))
	{
		p_obj->SetTranslation(p_obj->GetTransform().GetTranslation() + velocity * dt);
		p_obj->SetVelocity(0);
	}

	else
	{
		if (p_obj->GetRigidbody()->IsResistance())
			velocity *= p_obj->GetRigidbody()->GetDamping();
		p_obj->SetTranslation(p_obj->GetTransform().GetTranslation() + velocity * dt);
		p_obj->SetVelocity(velocity);
	}
	p_obj->force_accumlator = vector2(0, 0);
}

void Physics::resolveInterpenetration(Object* p_obj1, Object* p_obj2)
{
	if (p_obj1->move_type == MoveType::dynamic && p_obj2->move_type == MoveType::dynamic)
		return;

	if (p_obj1->move_type == MoveType::stay && p_obj2->move_type == MoveType::stay)
		return;

	Object* player;
	Object* wall;
	if (p_obj1->move_type == MoveType::dynamic)
	{
		player = p_obj1;
		wall = p_obj2;
	}
	else
	{
		player = p_obj2;
		wall = p_obj1;
	}

	vector2 playerPos = player->GetTransform().GetTranslation();
	vector2 wallPos = wall->GetTransform().GetTranslation();
	vector2 playernormal = playerPos - wallPos;

	float penetration = player->GetTransform().GetScale().x + wall->GetTransform().GetScale().x
		- distance_between(playerPos, wallPos);
	vector2 movePerIMass = playernormal * (penetration / (player->GetRigidbody()->GetMass() + wall->GetRigidbody()->GetMass()));
	vector2 particleMovement = movePerIMass * 1 / player->GetRigidbody()->GetMass();
	player->SetTranslation(playerPos + particleMovement);
}

void Physics::resolveInterAABB(Object* p_objA, Object* p_objB)
{
	//circle-box / circle-circle 둘다 한다(circle은 박스로 만들것임..)
	//사실 이거 야매임 맞는지 모르겠음
	vector2 Amin, Amax, Bmin, Bmax;
	if (p_objA->GetMesh().mesh_polygon_type == MeshPolygonType::Circle)
	{
		ComputeCircleToAABBMinMax(p_objA, Amin, Amax);
		m_collisionChecker.ComputeMinMaxAABB(p_objB, Bmin, Bmax);
	}
	else if (p_objB->GetMesh().mesh_polygon_type == MeshPolygonType::Circle)
	{
        m_collisionChecker.ComputeMinMaxAABB(p_objA, Amin, Amax);
		ComputeCircleToAABBMinMax(p_objB, Bmin, Bmax);
	}
	else
	{
        m_collisionChecker.ComputeMinMaxAABB(p_objA, Amin, Amax);
        m_collisionChecker.ComputeMinMaxAABB(p_objB, Bmin, Bmax);
	}

	vector2 Anormal = normalize(p_objA->GetTransform().GetTranslation() - p_objB->GetTransform().GetTranslation());

	vector2 penetrationvec;
	if (Amin.x > Bmin.x && Amin.x < Bmax.x)
		penetrationvec.x = Bmax.x - Amin.x;
	if (Amax.x > Bmin.x && Amax.x < Bmax.x)
		penetrationvec.x = Amax.x - Bmin.x;
	if (Amin.x > Bmin.x && Amax.x < Bmax.x)
		penetrationvec.x = 0;

	if (Amin.y > Bmin.y && Amin.y < Bmax.y)
		penetrationvec.y = Bmax.y - Amin.y;
	if (Amax.y > Bmin.y && Amax.y < Bmax.y)
		penetrationvec.y = Amax.y - Bmin.y;
	if (Amin.y > Bmin.y && Amax.y < Bmax.y)
		penetrationvec.y = 0;


	float penetration = magnitude(penetrationvec);
	vector2 movePerIMass = Anormal * (penetration / (p_objA->GetRigidbody()->GetMass() + p_objB->GetRigidbody()->GetMass()));
	//vector2 particleMovement = movePerIMass * 1 / p_objA->mass;
	if (p_objA->move_type == MoveType::dynamic)
		p_objA->SetTranslation(p_objA->GetTransform().GetTranslation() + movePerIMass * 1 / p_objA->GetRigidbody()->GetMass());
	if (p_objB->move_type == MoveType::dynamic)
		p_objB->SetTranslation(p_objB->GetTransform().GetTranslation() + movePerIMass * -1 / p_objB->GetRigidbody()->GetMass());
}

bool Physics::resolveVelocity(Object* p_obj1, Object* p_obj2) //circle-circle
{
	vector2 obj1_normal = p_obj1->GetTransform().GetTranslation() - p_obj2->GetTransform().GetTranslation();
	obj1_normal = normalize(obj1_normal);
	if (p_obj1->GetMesh().mesh_polygon_type == MeshPolygonType::Circle &&
		p_obj2->GetMesh().mesh_polygon_type == MeshPolygonType::Box)
		obj1_normal = ComputeNormalCircle_AABB(p_obj1, p_obj2);
	if (p_obj2->GetMesh().mesh_polygon_type == MeshPolygonType::Circle &&
		p_obj1->GetMesh().mesh_polygon_type == MeshPolygonType::Box)
		obj1_normal = -ComputeNormalCircle_AABB(p_obj2, p_obj1);
	//이건 원의 normal을 리턴하고 여기서 원하는 건 obj1의 normal이다

	float separatingVelocity = dot(p_obj1->GetVelocity() - p_obj2->GetVelocity(), obj1_normal);
	float newSepVelocity = -separatingVelocity * p_obj1->GetRigidbody()->GetRestitution();
	float deltaVelocity = newSepVelocity - separatingVelocity;

	if (separatingVelocity == 0)//Resting contact
	{
		vector2 accCausedVelocity = p_obj1->GetAcceleartion() + p_obj2->GetAcceleartion();
		float accCausedSepVelocity = dot(accCausedVelocity, obj1_normal) * m_duration;
		if (accCausedSepVelocity < 0)
		{
			newSepVelocity += p_obj1->GetRigidbody()->GetDamping() * accCausedSepVelocity;
			if (newSepVelocity < 0) newSepVelocity = 0;
		}
		return true;
	}

	if (separatingVelocity < 0)
	{
		float obj1InMass = 0; float obj2InMass = 0; //안 움직이면 mass는 0이다...
		if (p_obj1->move_type == MoveType::dynamic)
			obj1InMass = 1 / p_obj1->GetRigidbody()->GetMass();
		if (p_obj2->move_type == MoveType::dynamic)
			obj2InMass = 1 / p_obj2->GetRigidbody()->GetMass();

		float totalInverseMass = obj1InMass + obj2InMass;

		if (totalInverseMass <= 0) return false;

		float impulse = deltaVelocity / totalInverseMass;
		vector2 impulsePerIMass = obj1_normal * impulse;

		if (p_obj1->move_type == MoveType::dynamic && p_obj1->GetRigidbody()->IsSliding())
			p_obj1->AddVelocity(impulsePerIMass * (1 / p_obj1->GetRigidbody()->GetMass()));
		if (p_obj2->move_type == MoveType::dynamic&& p_obj2->GetRigidbody()->IsSliding())
			p_obj2->AddVelocity(impulsePerIMass * -(1 / p_obj2->GetRigidbody()->GetMass()));
		return true;
	}
	if (separatingVelocity > 0)
		return false; //충돌 가능성 없음: separating
    return false;
}

void Physics::ComputeCircleToAABBMinMax(Object* p_obj, vector2& min, vector2& max)
{
	vector2 maxpos, minpos = p_obj->GetTransform().GetTranslation();//p_obj->GetMesh().GetPoint(0);
	min = p_obj->GetTransform().GetTranslation() - p_obj->GetTransform().GetScale();
	max = p_obj->GetTransform().GetTranslation() + p_obj->GetTransform().GetScale();
}

vector2 Physics::ComputeNormalCircle_AABB(Object* Circle, Object* AABB)
{
	vector2 circlePos = Circle->GetTransform().GetTranslation();
	vector2 boxPos = AABB->GetTransform().GetTranslation();
	vector2 boxMin, boxMax;
	vector2 TopLeft = vector2{ boxMin.x,boxMax.y };
	vector2 BottomRight = vector2{ boxMax.x,boxMin.y };
	m_collisionChecker.ComputeMinMaxAABB(AABB, boxMin, boxMax);
	vector2 aabbContactPos;
	vector2 circleNormal;

	if (circlePos.x > boxMin.x && circlePos.x < boxMax.x)
	{
		aabbContactPos = vector2{ circlePos.x,boxMin.y };
		float distance = distance_between(circlePos, aabbContactPos);
		if (distance > distance_between(circlePos, vector2{ aabbContactPos.x,boxMax.y }))
			aabbContactPos.y = boxMax.y;

	}
	else if (circlePos.y > boxMin.y && circlePos.y < boxMax.y)
	{
		aabbContactPos = vector2{ boxMin.x, circlePos.y };
		float distance = distance_between(circlePos, aabbContactPos);
		if (distance > distance_between(circlePos, vector2{ boxMax.x, aabbContactPos.y }))
			aabbContactPos.x = boxMax.x;
	}
	else
	{
		aabbContactPos = boxMin;
		float distance = distance_between(circlePos, aabbContactPos);
		if (distance < distance_between(circlePos, boxMax))
		{
			aabbContactPos = boxMax;
			distance = distance_between(circlePos, aabbContactPos);
		}
		if (distance < distance_between(circlePos, TopLeft))
		{
			aabbContactPos = TopLeft;
			distance = distance_between(circlePos, aabbContactPos);
		}
		if (distance < distance_between(circlePos, BottomRight))
		{
			aabbContactPos = BottomRight;
			distance = distance_between(circlePos, aabbContactPos);
		}
	}
	return normalize(circlePos - aabbContactPos);
}

void Physics::Quit()
{
}