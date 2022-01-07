#pragma once
#include "Object.hpp"
class AntiEnemy : public Object
{
public:
	AntiEnemy();
	virtual bool Update() override;
	virtual void CollideWithType(ObjectType type) override;

private:
};

