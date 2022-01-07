#pragma once
#include "System.hpp"
#include "Text.hpp"
#include <vector>
#include <string>
#include <cassert>

class HudManager : public System
{
public:
	HudManager() = default;
	~HudManager() = default;

	bool Init() override;
	bool Update(float dt) override;
	void Quit() override;

public:
	void AddText(std::string p_textName, std::string p_textData);
	bool RemoveText(std::string p_textName);
	Text* GetText(std::string p_textName);
	int GetObjectCount() { return (int)m_hudList.size(); }
	std::map<std::string, Text*>* GetHudListPointer() { return &m_hudList; }

private:
	std::map<std::string, Text*> m_hudList;
};

