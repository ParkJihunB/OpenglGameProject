#pragma once
#include "vector2.hpp"

class RigidBody
{
public:
	RigidBody() = default;

public: //init
	void SetSliding(bool isSlide) { m_isSliding = isSlide; }
	void SetResistance(bool isResist) { m_isResistance = isResist; }

public://set
	void SetVelocity(vector2 vel) { m_velocity = vel; }
	void AddVelocity(vector2 vel) { m_velocity += vel; }
	void SetAcceleration(vector2 acc) { m_acceleration = acc; }
	void SetGravity(bool isGravity);

public://get
	float GetMass() { return m_mass; }
	bool IsKinematic() { return m_isKinematic; }
	bool IsSliding() { return m_isSliding; }
	bool IsResistance() { return m_isResistance; }
	vector2 GetVelocity() { return m_velocity; }
	vector2 GetAcceleration() { return m_acceleration; }
	float GetRestitution() { return m_restitution; }
	float GetDamping() { return m_damping; }

private:
	float m_mass = 1.f;
	bool m_useGravity = false;
	bool m_isKinematic = false;
	bool m_isSliding = true; //Object will slide like on ice //false: move only amount of vel*1(dt)
	bool m_isResistance = true; // damping(¸¶Âû·Â) will be multiplied every dt

	vector2 m_velocity = vector2(0, 0);
	vector2 m_acceleration = vector2(0, 0);

	float m_restitution = 1.f;
	float m_damping = 0.99f;
};

