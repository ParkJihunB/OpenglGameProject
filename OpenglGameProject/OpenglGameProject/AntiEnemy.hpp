#pragma once
#include "Object.hpp"
class AntiEnemy : public Object
{
public:
	AntiEnemy();
	virtual bool Update() override;
	virtual void CollideWithType(ObjectType type) override;
	void SetliveLeft(int lives) { liveLeft = lives; }
	void AddTexture(std::string path, vector2 size = vector2(0, 0));
private:
	void ChangeTexture();

private:
	int liveLeft = 0;
	int currentTexture = 0;
	std::vector<std::string> texturePaths;
	std::vector<vector2> sizeChange;
};

