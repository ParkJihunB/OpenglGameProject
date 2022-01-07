#pragma once
#include "System.hpp"
#include <map>
#include "State.hpp"
#include "Physics.hpp"

class StateManager : public System
{
public:
	StateManager() = default;
	~StateManager() = default;

	bool Init() override;
	bool Update(float dt) override;
	void Quit() override;

public:
	State* GetCurrentState() { return m_currentState; }
	void AddState(std::string p_stateID, State* p_state);
	void ChangeState();

private:
	State* m_currentState = nullptr;
	std::map<std::string, State*> m_stateList;
	bool m_pause = false;
	Physics* m_physics = nullptr;
};