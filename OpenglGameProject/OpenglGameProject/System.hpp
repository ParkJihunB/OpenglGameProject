#pragma once
class System
{
public:
	virtual ~System() = default;

	virtual bool Init() = 0;
	virtual bool Update(float dt) = 0;
	virtual void Quit() = 0;
};