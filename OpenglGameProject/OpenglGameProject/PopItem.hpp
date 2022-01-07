#pragma once
#include "Object.hpp"

class PopItem : public Object
{
public:
	PopItem();
	virtual bool Update() override;
	virtual void CollideWithType(ObjectType type) override;

private:
};

