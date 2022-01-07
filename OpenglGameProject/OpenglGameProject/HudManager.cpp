#include "HudManager.hpp"

bool HudManager::Init()
{
	m_hudList.clear();
	return true;
}

bool HudManager::Update(float dt)
{
	std::vector<std::string> remove_obj;
	for (std::map<std::string, Text*>::iterator it = m_hudList.begin();
		it != m_hudList.end(); ++it)
	{
		//Please do not remove right here...
		if(it->second->Update() == false)
			remove_obj.push_back(it->first);
	}
	for (int i = 0; i < remove_obj.size(); i++)
		RemoveText(remove_obj.at(i));
	return true;
}

void HudManager::Quit()
{
	for (std::map<std::string, Text*>::iterator it = m_hudList.begin();
		it != m_hudList.end(); ++it)
	{
		std::cout << "HudManager::Object: " << it->first << " is removed" << std::endl;
		delete(it->second);
	}
	m_hudList.clear();
}

void HudManager::AddText(std::string p_textName, std::string p_textData)
{
	if (m_hudList.find(p_textData) != m_hudList.end())
	{
		std::cout << "Try to add same name text" << std::endl;
		assert(false);
	}
	m_hudList.insert(std::make_pair(p_textName, new Text(p_textData)));
	std::cout << "ObjectManager::Object: " << p_textName << " is added" << std::endl;
}

bool HudManager::RemoveText(std::string p_textName)
{
	for (std::map<std::string, Text*>::iterator it = m_hudList.begin();
		it != m_hudList.end(); ++it)
	{
		if (it->first == p_textName)
		{
			delete(it->second);
			it = m_hudList.erase(it);
			std::cout << "Object: " << p_textName << " is removed" << std::endl;
			return true;
		}
	}
	return false;
}

Text * HudManager::GetText(std::string p_textName)
{
	auto target = m_hudList.find(p_textName);
	if (target == m_hudList.end()) assert(false); //There's no such object
	return target->second;
}
