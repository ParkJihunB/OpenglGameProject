#pragma once
#include "Object.hpp"

class CommonObject : public Object
{
public:
	CommonObject();
	virtual bool Update() override;
	virtual void CollideWithType(ObjectType type) override;

private:
};

