#include "StateManager.hpp"

bool StateManager::Init()
{
	m_stateList.clear();
	m_currentState = nullptr;
	m_physics = new Physics();
	return true;
}

bool StateManager::Update(float dt)
{
	if (m_currentState->IsLevelChange())
		ChangeState();

	if (!m_currentState->GetPause())
	{
		m_currentState->Update(dt);
		m_currentState->UpdateObjManager(dt);
		m_physics->Update(dt);
	}
	else m_currentState->PauseUpdate(dt);
	return true;
}

void StateManager::Quit()
{
	m_stateList.clear();
	delete m_physics;
}

void StateManager::AddState(std::string p_stateID, State * p_state)
{
	m_stateList.insert(std::make_pair(p_stateID, p_state));

	if (m_currentState == nullptr)
	{
		p_state->Load();
		p_state->Initialize();
		m_currentState = p_state;
		m_physics->GetObjManager(m_currentState->GetObjectManager());
	}
}

void StateManager::ChangeState()
{
	m_currentState->UnLoad();
	m_currentState = m_stateList.find(m_currentState->GetNextLevel())->second;

	std::cout << "State Changed" << std::endl << std::endl;
	m_currentState->Load();
	m_currentState->SetUp();
	m_currentState->Initialize();
	m_physics->GetObjManager(m_currentState->GetObjectManager());
}
