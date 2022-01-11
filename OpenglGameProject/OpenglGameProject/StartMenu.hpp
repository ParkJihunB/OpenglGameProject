#pragma once
#include "State.hpp"
#include "Text.hpp"

enum Stage
{
	breakout,
	spaceInvader,
	pacMan,
	count
};
class StartMenu : public State
{
public:
	void SetUp() override;
	bool Initialize() override;
	bool Update(float dt) override;
	bool PauseUpdate(float dt) override;
	void Quit() override;

private:
	Text* mainMenu;
	Text* breakOutText;
	Text* spaceInvaderText;
	Text* pacManText;
	int currentText = 0;
};

