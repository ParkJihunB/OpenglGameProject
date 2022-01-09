#include "ObjectManager.hpp"

bool ObjectManager::Init()
{
	m_objectList.clear();
	return true;
}

bool ObjectManager::Update(float dt)
{
	std::vector<std::string> remove_obj;
	for (std::map<std::string, Object*>::iterator it = m_objectList.begin();
		it != m_objectList.end(); ++it)
	{
		if (it->second->Update() == false) //if object return false delete obj
		{
			//Can't remove right here
			//RemoveObject function will delete current iterator
			remove_obj.push_back(it->first);
		}
		//it->second->IsCollide = false;
	}

	for (int i = 0; i < remove_obj.size(); i++)
		RemoveObject(remove_obj.at(i));

	return true;
}

void ObjectManager::Quit()
{
	for (std::map<std::string, Object*>::iterator it = m_objectList.begin();
		it != m_objectList.end(); ++it)
	{
		std::cout << "ObjectManager::Object: " << it->first << " is removed" << std::endl;
		delete (it->second);
	}

	m_objectList.clear();
}

void ObjectManager::AddObject(std::string p_objectName)
{
	auto target = m_objectList.find(p_objectName);
	m_objectList.insert(std::make_pair(p_objectName, new Object()));
	std::cout << "ObjectManager::Object: " << p_objectName << " is added" << std::endl;
	if (p_objectName == playerName) IsPlayerLive = false;
}

bool ObjectManager::RemoveObject(std::string p_objectName)
{
	for (std::map<std::string, Object*>::iterator it = m_objectList.begin();
		it != m_objectList.end(); ++it)
	{
		if (it->first == p_objectName)
		{
			delete (it->second);
			it->second = nullptr;
			it = m_objectList.erase(it);
			std::cout << "Object: " << p_objectName << " is removed" << std::endl;
			if (p_objectName == playerName) IsPlayerLive = false;
			return true;
		}
	}
	return false;
}

Object * ObjectManager::GetObject(std::string p_objectName)
{
	auto target = m_objectList.find(p_objectName);
	if (target == m_objectList.end())
	{
		//std::cout << p_objectName + "does not exist" << std::endl;
		//assert(false);
		return nullptr;
	}

	return target->second;
}

bool ObjectManager::FindObject(std::string p_objectName)
{
	auto target = m_objectList.find(p_objectName);
	if (target == m_objectList.end()) return false;
	return true;
}
