#pragma once
#include "State.hpp"
#include "CommonObject.hpp"
#include "Enemy.hpp"
#include "Player.hpp"

struct RiverEnemyStatus
{
	std::string name;
	const char* path;
	vector2 size;
};
namespace RiverEnemyType
{
	const RiverEnemyStatus plane{ "plane", "Asset/RiverRaid/enemyPlane.png", vector2(18, 6)};
	const RiverEnemyStatus boat{ "boat", "Asset/RiverRaid/boat.png", vector2(30, 8)};
};

class RiverRaid : public State
{
public:
	void SetUp() override;
	bool Initialize() override;
	bool Update(float dt) override;
	bool PauseUpdate(float dt) override;
	void Quit() override;

	void UpdateEnemy();
	void GameOver();

private:
	void BuildMaze();
	Enemy* BuildBlock(std::string name, vector2 pos, vector2 size, Color color);
	Enemy* BuildEnemy(std::string name, vector2 pos, RiverEnemyStatus status);
private:
	Player* player;
	std::vector<Enemy*> obstacles;
private:
	int blockCount = 0;
};

