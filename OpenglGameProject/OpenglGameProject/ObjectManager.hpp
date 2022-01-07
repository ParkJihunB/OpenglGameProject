#pragma once
#include "System.hpp"
#include "Object.hpp"
#include <map>
#include <cassert>
#include <string>

class ObjectManager : public System
{
public:
	ObjectManager() = default;
	~ObjectManager() = default;

	bool Init() override;
	bool Update(float dt) override;
	void Quit() override;

public:
	void AddObject(std::string p_objectName);
	bool RemoveObject(std::string p_objectName);
	Object* GetObject(std::string p_objectName);
	bool FindObject(std::string p_objectName);
	std::map <std::string, Object*>& GetObjectMap() { return m_objectList; } //WHY..?
	std::map <std::string, Object*>* GetObjectMapPointer() { return &m_objectList; }
	int GetObjectsCount() { return (int)(m_objectList.size()); }

public:
	template <typename T>
	T* AddObjectTemplate(std::string p_objectName);

private:
	std::map<std::string, Object*> m_objectList;
};

template<typename T>
inline T* ObjectManager::AddObjectTemplate(std::string p_objectName)
{
	if (m_objectList.find(p_objectName) != m_objectList.end())
	{
		std::cout << "Try to add same name object" << std::endl;
		assert(false);
	}	
	T* newObj = new T();
	m_objectList.insert(std::make_pair(p_objectName, newObj));
	std::cout << "ObjectManager::Object: " << p_objectName << " is added" << std::endl;
	return newObj;
}