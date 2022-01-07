/**
* @file Engine.hpp
* @brief Engine
* @details Engine sturcture
*/
#pragma once
#include <vector>
#include "System.hpp"
#include "Timer.hpp"
#include "Application.hpp"
#include "Graphic.hpp"
#include "StateManager.hpp"
#include "ObjectManager.hpp"
#include "HudManager.hpp"
#include "Physics.hpp"

/**
* @brief Engine
* @details game engine
*/
class Engine
{
public:
	bool Init(); //Add all system and initalize
	void Update(); //Update all systems
	void Quit(); //Quit all systems

public:
	void AddSystem(System* newSystem);

private:
	std::vector<System*> m_systemList;
	bool m_isQuit = false;

private:
	unsigned int m_width = 960;
	unsigned int m_height = 640;

	Timer m_timer;
	Application* m_application = nullptr;
	Graphic* m_graphic = nullptr;
	StateManager* m_stateManager = nullptr;
	State* m_state = nullptr;
	ObjectManager* m_objectManager = nullptr;
	HudManager* m_hudManager = nullptr;
};

