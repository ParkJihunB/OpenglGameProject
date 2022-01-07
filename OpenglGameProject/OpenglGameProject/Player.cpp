#include "Player.hpp"

Player::Player()
{
	m_objectType = ObjectType::player;
	AddRigidbody();
	GetRigidbody()->SetSliding(false);
	GetRigidbody()->SetResistance(false);
}

bool Player::Update()
{
	bool result = Object::Update();
	return result;
}

void Player::CollideWithType(ObjectType type)
{
	if (type == ObjectType::enemy) IsDelete = true;
}
