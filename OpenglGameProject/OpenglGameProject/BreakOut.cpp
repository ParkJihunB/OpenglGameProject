#include "BreakOut.hpp"

void BreakOut::SetUp()
{
	introCount = 0;
	gameStart = false;
	fallCount = 0;
}

bool BreakOut::Initialize()
{
	std::cout << "BreakOut" << std::endl;

	SetUpWall();
	SetUpBlocks();

	leftPlayer = BuildObjectTemplate<Player>("leftplayer", MeshPolygonType::Box);
	leftPlayer->SetScale(vector2(2.f, 2.f));
	leftPlayer->SetTranslation(vector2(playerInitPos.x - 6, playerInitPos.y));
	leftPlayer->SetColor(Common::Red);
	leftPlayer->SetDepth(-1.f);
	leftPlayer->move_type = MoveType::stay;

	rightPlayer = BuildObjectTemplate<Player>("rightplayer", MeshPolygonType::Box);
	rightPlayer->SetScale(vector2(2.f, 2.f));
	rightPlayer->SetTranslation(vector2(playerInitPos.x + 6, playerInitPos.y));
	rightPlayer->SetColor(Common::Red);
	rightPlayer->SetDepth(-1.f);
	rightPlayer->move_type = MoveType::stay;

	player = BuildObjectTemplate<Player>("player", MeshPolygonType::Box);
	player->SetScale(vector2(12.f, 2.f));
	player->SetTranslation(playerInitPos);
	player->SetColor(Common::White);
	player->move_type = MoveType::stay;
	player->SetDepth(0.f);
	RestrictPlayerMovement(vector2(1, 0));
	ChangePlayerVelocity(50.f);


	ball = BuildObjectTemplate<CommonObject>("ball", MeshPolygonType::Circle);
	ball->AddRigidbody();
	ball->SetScale(vector2(1.f, 1.f));
	ball->SetTranslation(ballInitPos);
	ball->SetColor(Common::pink);
	ball->GetRigidbody()->SetResistance(false);
	ball->GetRigidbody()->SetGravity(true);
	ball->SetVelocity(ballInitVel);
	ball->m_objectType = ObjectType::antipop;

	fallCountText = BuildText("FallCount", "Fall: 0");
	fallCountText->SetTransform(vector2(-0.85f, 0.85f));
	fallCountText->SetScale(1);
	fallCountText->SetColor(Common::White);
	fallCountText->SetDepth(-1.f);

	ChangeBackGroundColor(Common::Black);
	SetPause(true);
	return true;
}

bool BreakOut::Update(float dt)
{
	//PlayerMovement(player);
	UpdatePlayerAI();
	if (ball->GetTransform().GetTranslation().y < -45.f || ball->GetTransform().GetTranslation().y>35)
	{
		ballPrevPos = playerInitPos;
		player->SetTranslation(playerInitPos);
		leftPlayer->SetTranslation(vector2(playerInitPos.x - 6, playerInitPos.y));
		rightPlayer->SetTranslation(vector2(playerInitPos.x + 6, playerInitPos.y));
		ball->SetTranslation(ballInitPos);
		ball->SetVelocity(ballInitVel);
		fallCount++;
		fallCountText->ChangeText("Fall: " + std::to_string(fallCount));
		introCount = 0;
		gameStart = false;
		SetPause(true);
	}

	if (Input::IsKeyPressed(GLFW_KEY_SPACE))
		ChangeLevel("SpaceInvader");
	return true;
}

bool BreakOut::PauseUpdate(float dt)
{
	if (!gameStart) Intro(dt);
	return true;
}

void BreakOut::UpdatePlayerAI()
{
	vector2 playerDirection = ball->GetTransform().GetTranslation() - ballPrevPos;
	ballPrevPos = ball->GetTransform().GetTranslation();
	if (player->GetTransform().GetTranslation().x > 35)
	{
		if (playerDirection.x > 0) return;
	}
	else if (player->GetTransform().GetTranslation().x < -35)
	{
		if (playerDirection.x < 0) return;
	}
	player->AddVelocity(vector2(playerDirection.x*playerVel, 0));
	rightPlayer->AddVelocity(vector2(playerDirection.x * playerVel, 0));
	leftPlayer->AddVelocity(vector2(playerDirection.x * playerVel, 0));
}

void BreakOut::Quit()
{

}

void BreakOut::Intro(float dt)
{
	if (introCount >= 3)
	{
		SetPause(false);
		gameStart = true;
		std::cout << "Game Start" << std::endl;
	}
	introCount += dt;
}

void BreakOut::SetUpWall()
{
	BuildBox("top_wall", 1.0f, Common::Blue, vector2{ 0,25 });
	GetObjectManager()->GetObject("top_wall")->AddRigidbody();
	GetObjectManager()->GetObject("top_wall")->SetScale(vector2(80.f, 4.f));
	GetObjectManager()->GetObject("top_wall")->move_type = MoveType::stay;

	BuildBox("left_wall", 1.0f, Common::Blue, vector2{ -40,-1 });
	GetObjectManager()->GetObject("left_wall")->AddRigidbody();
	GetObjectManager()->GetObject("left_wall")->SetScale(vector2(4.f, 55.5f));
	GetObjectManager()->GetObject("left_wall")->move_type = MoveType::stay;

	BuildBox("right_wall", 1.0f, Common::Blue, vector2{ 40,-1 });
	GetObjectManager()->GetObject("right_wall")->AddRigidbody();
	GetObjectManager()->GetObject("right_wall")->SetScale(vector2(4.f, 55.5f));
	GetObjectManager()->GetObject("right_wall")->move_type = MoveType::stay;
}

void BreakOut::SetUpBlocks()
{
	int stringCount = 1;
	
	vector2 realBlockScale = vector2(4.8f, 1.8f);
	vector2 blockScale = vector2(5.f, 2.f);
	int rowNum = 7;
	int colNum = 11;//Please odd number and avoid multiple of 3(block variety)
	float startXpos = -(float(colNum) / 2.f - 0.5f) * blockScale.x;
	vector2 initPos = vector2(startXpos, 15.f);
	for (int i = 0; i < rowNum; i++) //row num
	{
		for (int j = 0; j < colNum; j++) //column
		{
			std::string block = "block";
			block.append(std::to_string(stringCount));
			Color blockColor = Common::Cyan;
			if (stringCount % 3 == 1) blockColor = Common::Magenta;
			else if (stringCount % 3 == 2) blockColor = Common::Yellow;

			PopItem* obj = BuildObjectTemplate<PopItem>(block, MeshPolygonType::Box);
			obj->SetScale(realBlockScale);
			obj->SetTranslation(initPos + vector2(blockScale.x * j, -(blockScale.y * i)));
			obj->SetColor(blockColor);
			obj->move_type = MoveType::stay;
			obj->AddRigidbody();
			stringCount++;
		}
	}
}