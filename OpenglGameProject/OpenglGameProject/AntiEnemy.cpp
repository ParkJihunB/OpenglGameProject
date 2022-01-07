#include "AntiEnemy.hpp"

AntiEnemy::AntiEnemy()
{
	m_objectType = ObjectType::antienemy;
}

bool AntiEnemy::Update()
{
	bool result = Object::Update();
	return result;
}

void AntiEnemy::CollideWithType(ObjectType type)
{
	if (type == ObjectType::enemy) IsDelete = true;
}
