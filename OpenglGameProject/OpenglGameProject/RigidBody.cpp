#include "RigidBody.hpp"

void RigidBody::SetGravity(bool isGravity)
{
	m_useGravity = isGravity;
	if (m_useGravity) m_acceleration += vector2(0, -9.81f);
}
