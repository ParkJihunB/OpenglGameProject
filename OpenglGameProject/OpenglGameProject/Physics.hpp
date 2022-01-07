#pragma once
#include "System.hpp"
#include "ObjectManager.hpp"
#include "CollisionChecker.hpp"

/*MEMO
    ComputeMinMaxAABB�� CollisionChecker������ ��������
    Resolve �� ���� ���δ� �׳� Object ������ ���� 
    �ƿ� Object->GetMinMax(vector2& min, vector2&max)
    �̷��� ���°� ������
    ������ �ϴ� CollisionChecker �� �־���� ���Ż糪��
*/
class Physics : public System
{
public:
	Physics() = default;
	~Physics() = default;

	bool Init() override;
	bool Update(float dt) override;
	void Quit() override;

	void GetObjManager(ObjectManager* p_objmanager);

private:
	void integrate(Object* p_obj, float dt);
	void resolveInterpenetration(Object* p_ojb1, Object* p_obj2);
	void resolveInterAABB(Object* p_obj1, Object* p_obj2);
	bool resolveVelocity(Object* p_obj1, Object* p_obj2);
	vector2 ComputeNormalCircle_AABB(Object* Circle, Object* AABB);
	void ComputeCircleToAABBMinMax(Object* p_obj, vector2& min, vector2& max);

private:
	//void ColliderCheck(Object* p_obj1, Object* p_obj2);
	//void RigidBodyCheck(Object* p_obj1, Object* p_obj2);

private:
	ObjectManager* m_objectmanager = nullptr;
	std::map<std::string, Object*>* m_objMap = nullptr;
	CollisionChecker m_collisionChecker;
	//Integrator m_integrator;
	float m_duration;
};

