#pragma once
#include "State.hpp"
#include "PopItem.hpp"
#include "Player.hpp"
#include "CommonObject.hpp"
#include "Enemy.hpp"
#include "AntiEnemy.hpp"
#include "Sound.hpp"

struct EnemyStatus
{
	std::string name;
	const char* path;
	vector2 size;
	int point;
};
namespace EnemyType
{
	//const 안 붙이면 여러번 정의된 어쩌고라고 함
	const EnemyStatus crab{ "crab", "Asset/SpaceInvader/crab.png", vector2(11, 9) ,20};
	const EnemyStatus octopus{ "octopus", "Asset/SpaceInvader/octopus.png", vector2(12, 8) ,10};
	const EnemyStatus spaceship{ "spaceship", "Asset/SpaceInvader/spaceship.png", vector2(16, 7) ,222};
	const EnemyStatus squid{ "squid", "Asset/SpaceInvader/squid.png", vector2(8, 8) ,30};
};
class SpaceInvader : public State
{
public:
	void SetUp() override;
	bool Initialize() override;
	bool Update(float dt) override;
	bool PauseUpdate(float dt) override;
	void Quit() override;

	void GameOver();

private:
	void BuildPlayer();
	void ResurrectPlayer();
	void UpdatePlayerLifeHud();
	void BuildBlock(AntiEnemy* obj, std::string name, vector2 pos);

	void BuildEnemies();
	Enemy* BuildEnemy(std::string name, EnemyStatus enemy, vector2 trans);

	void ShootBullet();
	void UpdateBullet();

	void UpdateEnemy(float dt);
	void EnemyBulletUpdate();
	void EnemyShoot();
	void EnemyMove();

private:
	Player* player;
	Enemy* alien;
	std::string enemiesName[5][11];
	AntiEnemy* bullet;
	AntiEnemy* block1;
	AntiEnemy* block2;
	AntiEnemy* block3;

	Text* scoreText;
	Text* LifeText;
	std::string playerLifeHud = "playerLifeHud";
	Sound* backgroundSound;
	Sound* shootingSound;

private:
	vector2 bulletSize = vector2(0.2, 1.5);
	vector2 bulletVel = vector2(0, 30);
	float bulletBoundary = 30.f;
	bool bulletChecked = true;

	vector2 playerSize = vector2(5, 5);
	float playerVel = 20;
	int playerSaveLife = 3;

	int enemyrowNum = 5;
	int enemycolNum = 11;
	vector2 enemyMovement = vector2(1, 0);
	float enemyVel = 1.f;
	int enemyBulletNum = 3;
	float enemyBulletTimeOut = 0.f;

private:
	float timeCount = 0;
	float enemyBulletCount = 0;
	int score = 0;
};