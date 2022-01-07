#pragma once
#include "State.hpp"
#include "PopItem.hpp"
#include "Player.hpp"
#include "CommonObject.hpp"

class BreakOut : public State
{
public:
	void SetUp() override;
	bool Initialize() override;
	bool Update(float dt) override;
	bool PauseUpdate(float dt) override;
	void Quit() override;


	void Intro(float dt);
	void SetUpWall();
	void SetUpBlocks();
	void UpdatePlayerAI();

private://Objects
	Object* player = nullptr;
	Object* ball = nullptr;
	Object* obj = nullptr;

	Object* leftPlayer = nullptr;
	Object* rightPlayer = nullptr;

private:
	Text* fallCountText = nullptr;

private:
	vector2 ballInitVel = vector2(30.f, 30.f);
	vector2 ballInitPos = vector2(0, -25);
	vector2 playerInitPos = vector2(0, -30);
	float playerVel = 45.f;
	float introCount = 0;
	bool gameStart = false;
	int fallCount = 0;

	vector2 ballPrevPos = ballInitPos;
};