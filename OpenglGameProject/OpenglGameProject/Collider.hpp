#pragma once
class Collider
{
public:
	Collider() = default;

public:
	void SetCollide(bool isCollide) { isColliding = isCollide; }

private:
	bool isTrigger = false;
	bool isColliding = false;
};

