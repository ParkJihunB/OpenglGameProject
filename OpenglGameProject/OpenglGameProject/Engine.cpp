/**
* @file Engine.cpp
* @brief Engine functions
*/
#include "Engine.hpp"
#include "StartMenu.hpp"
#include "BreakOut.hpp"
#include "SpaceInvader.hpp"
#include "StartMenu.hpp"
#include "RiverRaid.hpp"

/**
* @brief Engine initalize
* @details Add all systems and level and initalize
* @param
* @return true if initalize success
*/
bool Engine::Init()
{
	m_systemList.clear();

	//Create all systems
	m_application = new Application(m_width, m_height); //create opengl window
	m_graphic = new Graphic(m_width, m_height);
	m_stateManager = new StateManager();
	//m_physics = new Physics();

	//Add systems to system list
	AddSystem(m_application);
	AddSystem(m_graphic);
	AddSystem(m_stateManager);

	//Init all systems
	for (auto i : m_systemList) i->Init();

	//Add all state(load all)
	m_stateManager->AddState("StartMenu", new StartMenu());
	m_stateManager->AddState("BreakOut", new BreakOut());
	m_stateManager->AddState("SpaceInvader", new SpaceInvader());
	m_stateManager->AddState("RiverRaid", new RiverRaid());
	
	m_state = m_stateManager->GetCurrentState();
	m_objectManager = m_state->GetObjectManager();
	m_hudManager = m_state->GetHudManager();

	//m_timer.ResetTimeStamp();
	return true;
}

/**
* @brief Engine update
* @details Update all systems and levels
*/
void Engine::Update()
{
	while (!m_isQuit)
	{
		float dt = (float)m_timer.GetElapsedSeconds();
		m_timer.ResetTimeStamp();
		
		for (auto i : m_systemList) //Systems and Levels update
		{
			if (i->Update(dt) == false) m_isQuit = true;
		}

		m_state = m_stateManager->GetCurrentState();
		m_objectManager = m_state->GetObjectManager();
		m_hudManager = m_state->GetHudManager();

		m_graphic->Draw(m_objectManager);
		m_graphic->Draw(m_hudManager);
		m_graphic->ChangeBackGroundColor(m_state->GetBackgroundColor());
	}
}

/**
* @brief quit engine
* @details quit all levels and systems
*/
void Engine::Quit()
{
	for (auto i : m_systemList)
	{
		i->Quit();
		delete i;
	}
	m_systemList.clear();
}

/**
* @brief add system
* @details add system to system list
*/
void Engine::AddSystem(System * newSystem)
{
	m_systemList.push_back(newSystem);
}
