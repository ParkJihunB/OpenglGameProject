#pragma once
#include "Object.hpp"
class Enemy : public Object
{
public:
	Enemy();
	virtual bool Update() override;
	virtual void CollideWithType(ObjectType type) override;

	void PopWithPlayer(bool pop) { popWithPlayer = pop; }
private:
	bool popWithPlayer = false;
};

