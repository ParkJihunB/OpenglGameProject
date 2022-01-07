#pragma once

#include "Mesh.hpp"
#include "Transform.hpp"
#include "RigidBody.hpp"
//#include "Collider.hpp"

enum ObjectType
{
	player,
	enemy,
	pop,
	block,
	popitem,
	antipop,
	antienemy
};

enum MoveType
{
	dynamic,
	stay
};


class Object
{
public:
	Object() = default;
	Object(const Mesh& display_mesh, const Color& display_color);
	virtual bool Update();
	virtual void CollideWithType(ObjectType type) {};
	ObjectType m_objectType;

public:
	void SetMesh(Mesh p_mesh);
	void SetColor(Color p_color);
	void ChangeColor(Color p_color);
	void SetTranslation(const vector2& p_position);
	void SetScale(const vector2& p_scale);
	void SetRotation(const float& p_rotation);
	void SetDepth(const float& p_depth);

	Mesh& GetMesh() { return mesh; }
	Transform& GetTransform() { return transform; }


	Mesh mesh;
	Transform transform;
	bool IsDelete = false;


public:
	void SetVelocity(vector2 value) { m_rigidbody->SetVelocity(value); }
	void AddVelocity(vector2 value) { m_rigidbody->AddVelocity(value); }
	vector2 GetVelocity() { return m_rigidbody->GetVelocity(); }
	void SetAcceleration(vector2 acc) { m_rigidbody->SetAcceleration(acc); }
	vector2 GetAcceleartion() { return m_rigidbody->GetAcceleration(); }
	void AddForce(vector2 force) { force_accumlator += force; }

	void SetCollision(bool p_iscollide) { IsCollide = p_iscollide; }
	void SetInitPosiiton(vector2 p_trans) { prev_position = p_trans; }

	ObjectType type;
	bool IsCollide = false;
	bool IsGhost = false; //just check the collide stay ghost
	int move_type = MoveType::dynamic;
	vector2 prev_position;

	vector2 force_accumlator;


public:
	//void AddCollider() { m_collider = new Collider; }
	void AddRigidbody() { m_rigidbody = new RigidBody; }
	RigidBody* GetRigidbody() { return m_rigidbody; }
	//Collider* GetCollider() { return m_collider; }

private:
	RigidBody* m_rigidbody = nullptr;
	//Collider* m_collider = nullptr;
};