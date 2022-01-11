#include "StartMenu.hpp"

void StartMenu::SetUp()
{
}

bool StartMenu::Initialize()
{
	ChangeBackGroundColor(Common::Black);
	float posY = 0.2f;
	float intervalY = 0.25f;

	mainMenu = BuildText("mainMenu", "MAIN MENU");
	mainMenu->SetTransform(vector2(-0.4, posY + intervalY * 1));
	mainMenu->SetScale(1.5);
	mainMenu->SetColor(Common::White);

	breakOutText = BuildText("breakOut", "Break Out");
	breakOutText->SetTransform(vector2(-0.27 + 0.05, posY - intervalY));
	breakOutText->SetScale(1);
	breakOutText->SetColor(Common::Blue);

	spaceInvaderText = BuildText("spaceInvader", "Space Invader");
	spaceInvaderText->SetTransform(vector2(-0.35 + 0.05, posY - intervalY*2));
	spaceInvaderText->SetScale(1);
	spaceInvaderText->SetColor(Common::White);

	pacManText = BuildText("River Raid", "River Raid");
	pacManText->SetTransform(vector2(-0.28 + 0.05, posY - intervalY*3));
	pacManText->SetScale(1);
	pacManText->SetColor(Common::White);

	return true;
}

bool StartMenu::Update(float dt)
{
	if (Input::IsKeyAnyPressed())
	{
		if (Input::IsKeyPressed(GLFW_KEY_S)) currentText++;
		else if (Input::IsKeyPressed(GLFW_KEY_W)) currentText--;

		if (currentText < 0) currentText = Stage::count-1;
		else if (currentText >= Stage::count) currentText = 0;
		if (currentText == Stage::breakout)
		{
			breakOutText->SetColor(Common::Blue);
			spaceInvaderText->SetColor(Common::White);
			pacManText->SetColor(Common::White);
		}
		else if (currentText == Stage::spaceInvader)
		{
			breakOutText->SetColor(Common::White);
			spaceInvaderText->SetColor(Common::Blue);
			pacManText->SetColor(Common::White);
		}
		else if (currentText == Stage::pacMan)
		{
			breakOutText->SetColor(Common::White);
			spaceInvaderText->SetColor(Common::White);
			pacManText->SetColor(Common::Blue);
		}

		if (Input::IsKeyPressed(GLFW_KEY_SPACE))
		{
			switch (currentText)
			{
			case Stage::breakout:
				ChangeLevel("BreakOut");
				break;
			case Stage::spaceInvader:
				ChangeLevel("SpaceInvader");
				break;
			case Stage::pacMan:
				ChangeLevel("RiverRaid");
				break;
			}
		}
	}


	return true;
}

bool StartMenu::PauseUpdate(float dt)
{
	return false;
}

void StartMenu::Quit()
{
}
