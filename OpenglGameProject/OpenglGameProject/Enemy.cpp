#include "Enemy.hpp"

Enemy::Enemy()
{
	m_objectType = ObjectType::enemy;
}

bool Enemy::Update()
{
	bool result = Object::Update();
	return result;
}

void Enemy::CollideWithType(ObjectType type)
{
	if (type == ObjectType::antienemy) IsDelete = true;
}
