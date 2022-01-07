#pragma once
#include "Object.hpp"

class Player: public Object
{
public:
	Player();
	virtual bool Update() override;
	virtual void CollideWithType(ObjectType type) override;

private:
	
};

