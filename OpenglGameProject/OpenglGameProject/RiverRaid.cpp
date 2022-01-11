#include "RiverRaid.hpp"

void RiverRaid::SetUp()
{
}

bool RiverRaid::Initialize()
{
	ChangeBackGroundColor(Common::Cyan);
	
	player = BuildTextureTemplate<Player>("player", MeshPolygonType::Box);
	player->GetMesh().CreateTexture("Asset/RiverRaid/plane.png", TextureType::PNG);
	player->SetScale(vector2(6, 7));
	player->SetTranslation(vector2(-40.f, 0.f));
	player->SetColor(Common::Black);
	player->move_type = MoveType::stay;
	ChangePlayerVelocity(20.f);

	BuildMaze();
	obstacles.push_back(BuildEnemy("boat1", vector2(-20, 20), RiverEnemyType::boat));
	obstacles.push_back(BuildEnemy("boat2", vector2(30, 0), RiverEnemyType::boat));
	obstacles.push_back(BuildEnemy("plane1", vector2(0, 10), RiverEnemyType::plane));
	obstacles.push_back(BuildEnemy("plane2", vector2(40, -10), RiverEnemyType::plane));
	return true;
}

bool RiverRaid::Update(float dt)
{
	PlayerMovement(player);
	UpdateEnemy();
	if (!GetObjectManager()->IsPlayerAlive())
	{
		GameOver();
		SetPause(true);
	}

	return true;
}

bool RiverRaid::PauseUpdate(float dt)
{
	if (Input::IsKeyPressed(GLFW_KEY_SPACE))
		ChangeLevel("StartMenu");
	return true;
}

void RiverRaid::Quit()
{
}

void RiverRaid::UpdateEnemy()
{
	for (int i = 0; i < obstacles.size(); i++)
	{
		vector2 pos = obstacles[i]->GetTransform().GetTranslation();
		if (pos.x < -55)
		{
			pos.x = 50+rand() % 30;
			pos.y = rand() % 40 - 20;
		}
		else
			pos.x -= 0.4f;
		obstacles[i]->GetTransform().SetTranslation(pos);
	}
}

void RiverRaid::GameOver()
{
	BuildBlock("GameOverPanel", vector2(0, 0), vector2(180, 100), Common::Black);
	Text* GameOverText = BuildText("GameOverText", "Game Over");
	GameOverText->SetTransform(vector2(-0.25, 0.2));
	GameOverText->SetScale(1);
	GameOverText->SetColor(Common::White);
	GameOverText->SetDepth(-1.f);

	Text* ReturnToStart = BuildText("ReturnToStart", "Return to start menu");
	ReturnToStart->SetTransform(vector2(-0.45, -0.25));
	ReturnToStart->SetScale(1);
	ReturnToStart->SetColor(Common::Blue);
	ReturnToStart->SetDepth(-1.f);
}

void RiverRaid::BuildMaze()
{
	BuildBlock("bridgeUp", vector2(0, 30), vector2(300, 30), Common::grass);
	BuildBlock("bridgeDown", vector2(0, -30), vector2(300, 30), Common::grass);
}

Enemy* RiverRaid::BuildBlock(std::string name, vector2 pos, vector2 size, Color color)
{
	Enemy* block = BuildObjectTemplate<Enemy>(name, MeshPolygonType::Box);
	block->AddRigidbody();
	block->GetRigidbody()->SetResistance(false);
	block->SetScale(size / 3.f);
	block->SetColor(color);
	block->SetTranslation(pos);
	blockCount++;
	return block;
}

Enemy * RiverRaid::BuildEnemy(std::string name, vector2 pos, RiverEnemyStatus status)
{
	Enemy* e = BuildTextureTemplate<Enemy>(name, MeshPolygonType::Box);
	e->GetMesh().CreateTexture(status.path, TextureType::PNG);
	e->AddRigidbody();
	e->GetRigidbody()->SetResistance(false);
	e->SetScale(status.size / 2.f);
	e->SetColor(Common::White);
	e->SetTranslation(pos);
	return e;
}
