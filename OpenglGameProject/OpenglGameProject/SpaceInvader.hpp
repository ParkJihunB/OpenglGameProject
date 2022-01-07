#pragma once
#include "State.hpp"
#include "PopItem.hpp"
#include "Player.hpp"
#include "CommonObject.hpp"
#include "Enemy.hpp"
#include "AntiEnemy.hpp"

struct EnemyStatus
{
	const char* path;
	vector2 size;
};
namespace EnemyType
{
	//const 안 붙이면 여러번 정의된 어쩌고라고 함
	const EnemyStatus crab{ "Asset/SpaceInvader/crab.png", vector2(11, 9) };
	const EnemyStatus octopus{ "Asset/SpaceInvader/octopus.png", vector2(12, 8) };
	const EnemyStatus spaceship{ "Asset/SpaceInvader/spaceship.png", vector2(16, 7) };
	const EnemyStatus squid{ "Asset/SpaceInvader/squid.png", vector2(8, 8) };
};
class SpaceInvader : public State
{
public:
	void SetUp() override;
	bool Initialize() override;
	bool Update(float dt) override;
	bool PauseUpdate(float dt) override;
	void Quit() override;

private:
	void BuildEnemies();
	Enemy* BuildEnemy(std::string name, EnemyStatus enemy, vector2 trans);
	void ShootBullet();
	void UpdateBullet();
	void EnemyUpdate();
	void BlockUpdate();

private:
	Player* player;
	Enemy* alien;
	AntiEnemy* bullet;
	std::vector<std::string> enemies;
	AntiEnemy* block;

	Text* scoreText;

private:
	vector2 bulletSize = vector2(0.2, 1.5);
	vector2 bulletVel = vector2(0, 30);
	float bulletBoundary = 30.f;
	bool bulletChecked = true;
	vector2 playerSize = vector2(5, 5);
	float playerVel = 20;
	vector2 enemyMovement = vector2(1, 0);
	float enemyVel = 1.f;

private:
	float timeCount = 0;
	int score = 0;
};