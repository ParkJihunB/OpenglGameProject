#include "SpaceInvader.hpp"

void SpaceInvader::SetUp()
{
}

bool SpaceInvader::Initialize()
{
	std::cout << "Space Invader" << std::endl;
	ChangeBackGroundColor(Common::Black);
	BuildEnemies();

	player = BuildTextureTemplate<Player>("player", MeshPolygonType::Box);
	player->GetMesh().CreateTexture("Asset/SpaceInvader/player.png", TextureType::PNG);
	player->SetScale(vector2(5, 5));
	player->SetTranslation(vector2(0.f, -25.f));
	player->SetColor(Common::Green);
	player->move_type = MoveType::stay;
	RestrictPlayerMovement(vector2(1, 0));
	ChangePlayerVelocity(playerVel);

	block = BuildTextureTemplate<AntiEnemy>("block1", MeshPolygonType::Box);
	block->GetMesh().CreateTexture("Asset/SpaceInvader/block.png", TextureType::PNG);
	block->AddRigidbody();
	block->SetScale(vector2(18/2, 12/2));
	block->SetTranslation(vector2(-25.f, -18.f));
	block->SetColor(Common::White);
	block->move_type = MoveType::stay;
	

	scoreText = BuildText("Score 0", "Fall: 0");
	scoreText->SetTransform(vector2(-0.85f, 0.85f));
	scoreText->SetScale(1);
	scoreText->SetColor(Common::White);
	scoreText->SetDepth(-1.f);

	timeCount = 7.5f;
	return true;
}

bool SpaceInvader::Update(float dt)
{
	PlayerMovement(player);
	UpdateBullet();
	timeCount += dt;
	if (timeCount > 15.f)
	{
		EnemyUpdate();
		timeCount = 0;
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

void SpaceInvader::EnemyUpdate()
{
	std::cout << "update the enemy" << std::endl;
	enemyMovement *= -1;
	for (auto it = enemies.begin(); it != enemies.end();)
	{
		Object* temp = GetObjectManager()->GetObject(*it);
		vector2 trans = temp->GetTransform().GetTranslation();
		trans.y -= 0.5f;
		temp->SetTranslation(trans);
		temp->SetVelocity(enemyMovement * enemyVel);
		it++;
	}
}

void SpaceInvader::BlockUpdate()
{
	std::cout << "Update" << std::endl;
	block->GetMesh().texture->ChangeTexture("Asset/SpaceInvader/block1.png");
}

void SpaceInvader::UpdateBullet()
{
	if (!GetObjectManager()->FindObject("bullet"))
	{
		if (bulletChecked) return;
		for (auto it = enemies.begin(); it != enemies.end(); it++)
		{
			if (!GetObjectManager()->FindObject(*it))
			{
				it = enemies.erase(it);
				score += 10;
				scoreText->ChangeText("Point " + std::to_string(score));
				break;
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
}


void SpaceInvader::BuildEnemies()
{
	std::string name = "alien";
	int count = 0;
	vector2 interval = vector2(7, 5);
	int rowNum = 5;
	int colNum = 11;
	vector2 startPos = vector2(-((float)colNum/2.f - 0.5f)*interval.x, 5);
	Enemy* e = nullptr;
	for (int i = 0; i < rowNum; i++)
	{
		for (int j = 0; j < colNum; j++)
		{
			vector2 pos = vector2(startPos.x + interval.x * j, startPos.y + interval.y * i);
			if (i == 0)
				e = BuildEnemy(name+std::to_string(count), EnemyType::squid, pos);
			else if(i>0 && i < 3)
				e = BuildEnemy(name + std::to_string(count), EnemyType::crab, pos);
			else
				e = BuildEnemy(name + std::to_string(count), EnemyType::octopus, pos);
			enemies.push_back(name + std::to_string(count));
			count++;	
		}
	}
	EnemyUpdate();
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

