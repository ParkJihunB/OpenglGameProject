#include "SpaceInvader.hpp"

void SpaceInvader::SetUp()
{
}

bool SpaceInvader::Initialize()
{
	std::cout << "Space Invader" << std::endl;
	ChangeBackGroundColor(Common::Black);
	
	BuildEnemies();
	BuildPlayer();
	for (int i = 0; i < playerSaveLife; i++)
	{
		CommonObject* hud = BuildTextureTemplate<CommonObject>(playerLifeHud + std::to_string(i), MeshPolygonType::Box);
		hud->GetMesh().CreateTexture("Asset/SpaceInvader/player.png",TextureType::PNG);
		hud->SetScale(vector2(int(11.f/2), int(7.f/2)));
		hud->SetTranslation(vector2(30+ i * 6, 29));
		hud->SetColor(Common::Green);
		hud->SetDepth(-1.f);
	}

	BuildBlock(block1, "block1", vector2(-25.f, -18.f));
	BuildBlock(block2, "block2", vector2(0, -18.f));
	BuildBlock(block3, "block3", vector2(25.f, -18.f));;

	scoreText = BuildText("Score", "Fall: 0");
	scoreText->SetTransform(vector2(-0.85f, 0.85f));
	scoreText->SetScale(1);
	scoreText->SetColor(Common::White);
	scoreText->SetDepth(-1.f);

	LifeText = BuildText("Life", "Life");
	LifeText->SetTransform(vector2(0.35f, 0.85f));
	LifeText->SetScale(1);
	LifeText->SetColor(Common::White);
	LifeText->SetDepth(-1.f);

	backgroundSound = new Sound("Asset/SpaceInvader/breakout.mp3");
	backgroundSound->SetLoop(true);
	backgroundSound->Init();
	backgroundSound->PlaySound();

	shootingSound = new Sound("Asset/SpaceInvader/bleep.mp3");
	shootingSound->Init();

	timeCount = 7.5f;
	return true;
}

bool SpaceInvader::Update(float dt)
{
	PlayerMovement(player);
	UpdateBullet();
	timeCount += dt;
	enemyBulletCount += dt;
	enemyBulletTimeOut += dt;
	if (timeCount > 15.f)
	{
		EnemyMove();
		timeCount = 0;
	}
	if (enemyBulletCount > 3.f) 
	{
		EnemyShoot();
		enemyBulletCount = 0;
	}

	if (enemyBulletTimeOut > 6.f)
	{
		EnemyBulletUpdate();
		enemyBulletTimeOut = 0;
	}

	if (Input::IsKeyPressed(GLFW_KEY_SPACE))
		ShootBullet();
	
	return true;
}

bool SpaceInvader::PauseUpdate(float dt)
{
	return true;
}

void SpaceInvader::Quit()
{
}

void SpaceInvader::GameOver()
{
}

void SpaceInvader::UpdateEnemy(float dt)
{
}

void SpaceInvader::EnemyBulletUpdate()
{
	for (int i = 0; i < enemyBulletNum; i++)
	{
		std::string bulletName = "enemyBullet" + std::to_string(i);
		if (!GetObjectManager()->FindObject(bulletName)) continue;
		GetObjectManager()->RemoveObject(bulletName);
	}
	if (!GetObjectManager()->IsPlayerAlive())
		ResurrectPlayer();
}

void SpaceInvader::EnemyShoot()
{
	/*
	Enemies name [i][j]
	20 21 22 23 24 
	10 11 12 13 14
	00 01 02 03 04

	20 21 22    24 ^
	10 11 12    14 |
	00    02    04 | 이렇게 검사해서 가장 먼저 나오는 적을 저장.
	*/
	
	std::vector<std::string> shootList;

	for (int j = 0; j < enemycolNum; j++) //가장 아래에 있는 적을 저장
	{
		for (int i = 0; i < enemyrowNum; i++)
		{
			if (enemiesName[i][j] == "") continue;
			shootList.push_back(enemiesName[i][j]);
			break;
		}
	}
	
	for (int i = 0; i < enemyBulletNum; i++) //가장 아래에 있는 적 중 랜덤하게 골라서 총 발사
	{
 		if (shootList.size() <= 0) break;

		std::string bulletName = "enemyBullet" + std::to_string(i);
		GetObjectManager()->RemoveObject(bulletName);
		

		//Create Enemy Bullet
		int num = rand() % shootList.size();
		Object* obj = GetObjectManager()->GetObject(shootList.at(num));
		if (obj == nullptr) continue;
		Enemy* bullet = BuildObjectTemplate<Enemy>(bulletName, MeshPolygonType::Box);
		bullet->AddRigidbody();
		bullet->GetRigidbody()->SetResistance(false);
		bullet->SetScale(bulletSize);
		vector2 pos = obj->GetTransform().GetTranslation();
		pos.y -= (bulletSize.y / 2.f + 5.f);
		bullet->SetTranslation(pos);
		bullet->SetColor(Common::White);
		bullet->SetVelocity(-bulletVel);
		bullet->PopWithPlayer(true);

		shootList.erase(shootList.begin() + num);
	}
}

void SpaceInvader::EnemyMove()
{
	enemyMovement *= -1;

	for (int i = 0; i < enemyrowNum; i++)
	{
		for (int j = 0; j < enemycolNum; j++)
		{
			if (enemiesName[i][j] == "") continue;
			if (!GetObjectManager()->FindObject(enemiesName[i][j]))
			{
				enemiesName[i][j] = "";
				continue;
			}
			Object* temp = GetObjectManager()->GetObject(enemiesName[i][j]);
			vector2 trans = temp->GetTransform().GetTranslation();
			trans.y -= 0.5f;
			temp->SetTranslation(trans);
			temp->SetVelocity(enemyMovement * enemyVel);
		}
	}
}

void SpaceInvader::UpdateBullet()
{
	if (!GetObjectManager()->FindObject("bullet"))
	{
		if (bulletChecked) return;

		for (int i = 0; i < enemyrowNum; i++)
		{
			for (int j = 0; j < enemycolNum; j++)
			{
				if (!GetObjectManager()->FindObject(enemiesName[i][j]))
				{
					int point;
					if (enemiesName[i][j].find(EnemyType::squid.name))
						point = EnemyType::squid.point;
					if (enemiesName[i][j].find(EnemyType::crab.name))
						point = EnemyType::crab.point;
					if (enemiesName[i][j].find(EnemyType::octopus.name))
						point = EnemyType::octopus.point;
					enemiesName[i][j] = "";
					score += point;
					scoreText->ChangeText("Point " + std::to_string(score));
					break;
				}
			}
		}
		bulletChecked = true;
		return;
	}
	if (bullet->GetTransform().GetTranslation().y > bulletBoundary)
	{
		GetObjectManager()->RemoveObject("bullet");
		return;
	}
	if (bulletChecked) return;
}

void SpaceInvader::ShootBullet()
{
	if (GetObjectManager()->FindObject("bullet")) return;
	bullet = BuildObjectTemplate<AntiEnemy>("bullet", MeshPolygonType::Box);
	bullet->AddRigidbody();
	bullet->GetRigidbody()->SetResistance(false);
	bullet->SetScale(bulletSize);
	vector2 pos = player->GetTransform().GetTranslation();
	pos.y += bulletSize.y / 2.f + playerSize.y / 2.f;
	bullet->SetTranslation(pos);
	bullet->SetColor(Common::White);
	bullet->AddVelocity(bulletVel);
	bulletChecked = false;
	shootingSound->PlaySound();
}


void SpaceInvader::BuildPlayer()
{
 	player = BuildTextureTemplate<Player>("player", MeshPolygonType::Box);
	player->GetMesh().CreateTexture("Asset/SpaceInvader/player.png", TextureType::PNG);
	player->SetScale(vector2(5, 5));
	player->SetTranslation(vector2(0.f, -25.f));
	player->SetColor(Common::Green);
	player->move_type = MoveType::stay;
	RestrictPlayerMovement(vector2(1, 0));
	ChangePlayerVelocity(playerVel);
}

void SpaceInvader::ResurrectPlayer()
{
	playerSaveLife--;
	if (playerSaveLife > 0)
	{
		BuildPlayer();
		UpdatePlayerLifeHud();
	}
	else
		GameOver();
}

void SpaceInvader::UpdatePlayerLifeHud()
{
	GetObjectManager()->RemoveObject(playerLifeHud + std::to_string(playerSaveLife));
}

void SpaceInvader::BuildBlock(AntiEnemy* obj, std::string name, vector2 pos)
{
	obj = BuildTextureTemplate<AntiEnemy>(name, MeshPolygonType::Box);
	obj->GetMesh().CreateTexture("Asset/SpaceInvader/block.png", TextureType::PNG);
	obj->AddRigidbody();
	obj->SetScale(vector2(18 / 2, 12 / 2));
	obj->SetTranslation(pos);
	obj->SetColor(Common::White);
	obj->move_type = MoveType::stay;
	obj->SetliveLeft(4);
	obj->AddTexture("Asset/SpaceInvader/block1.png");
	obj->AddTexture("Asset/SpaceInvader/block2.png");
	obj->AddTexture("Asset/SpaceInvader/block3.png", vector2(18.f / 2.f, 9.f / 2.f));
	obj->AddTexture("Asset/SpaceInvader/block4.png", vector2(18.f / 2.f, 6.f / 2.f));
}

void SpaceInvader::BuildEnemies()
{
	EnemyStatus enemyType;
	vector2 interval = vector2(7, 5);
	vector2 startPos = vector2(-((float)enemycolNum/2.f - 0.5f)*interval.x, 5);
	for (int i = 0; i < enemyrowNum; i++)
	{
		for (int j = 0; j < enemycolNum; j++)
		{
			vector2 pos = vector2(startPos.x + interval.x * j, startPos.y + interval.y * i);
			std::string nameCount = std::to_string(i) + std::to_string(j);

			if (i == 0)
				enemyType = EnemyType::squid;
				
			else if (i > 0 && i < 3)
				enemyType = EnemyType::crab;
				
			else
				enemyType = EnemyType::octopus;
			BuildEnemy(enemyType.name+ nameCount,enemyType, pos);
			enemiesName[i][j] = enemyType.name + nameCount;
		}
	}
	EnemyMove();
}

Enemy* SpaceInvader::BuildEnemy(std::string name, EnemyStatus enemy, vector2 trans)
{
	Enemy* e = BuildTextureTemplate<Enemy>(name, MeshPolygonType::Box);
	e->GetMesh().CreateTexture(enemy.path, TextureType::PNG);
	e->AddRigidbody();
	e->GetRigidbody()->SetResistance(false);
	e->SetScale(enemy.size/3.f);
	e->SetColor(Common::White);
	e->move_type = MoveType::stay;
	e->SetTranslation(trans);
	return e;
}

