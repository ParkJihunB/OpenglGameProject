#pragma once
#include "ObjectManager.hpp"
#include "HudManager.hpp"
#include "Input.hpp"

class State
{
public:
	virtual ~State() = default;

	/*every time each state is created/changed/load
	make each new state's objectmanager, reset level_change button*/
	virtual void Load();
	virtual void SetUp() = 0;
	virtual bool Initialize() = 0;
	virtual bool Update(float dt) = 0;
	virtual bool PauseUpdate(float dt) = 0;
	virtual void UnLoad();
	virtual void Quit() = 0;

public:
	ObjectManager* GetObjectManager() { return objectmanager; }
	HudManager* GetHudManager() { return hudManager; }
	void UpdateObjManager(float dt) { objectmanager->Update(dt); }
	void ChangeLevel(std::string p_nextLevel); //From level
	std::string GetNextLevel() { return m_nextLevel; }  //To StateManager
	bool IsLevelChange() { return level_change; }		//To StateManager
	void SetPause(bool pause);
	bool GetPause() { return isPaused; }

public:
	template<typename T>
	T* BuildObjectTemplate(std::string p_name, MeshPolygonType type);
	template<typename T>
	T* BuildTextureTemplate(std::string p_name, MeshPolygonType type);

public: //used in level
	Color GetBackgroundColor() { return background_color; }
	void ChangeBackGroundColor(Color p_color) { background_color = p_color; }

	Object* BuildBox(std::string p_name, float p_scale, Color p_color, vector2 p_trans = vector2{ 0.f, 0.f });
	Object* BuildCircle(std::string p_name, float p_scale, Color p_color, vector2 p_trans = vector2{ 0.f,0.f });
	Object* BuildCircle(std::string p_name, float p_scale, Color p_color, vector2 p_trans, ObjectType p_type);
	Object* BuildLine(std::string p_name, vector2 start, vector2 end, Color p_color);
	Text* BuildText(std::string p_name, std::string textData);

	void PlayerMovement(Object* p_player);
	void ChangePlayerVelocity(float p_velocity) { player_velocity = p_velocity; }
	void RestrictPlayerMovement(vector2 p_restrictVec) { playerRestrictedVec = p_restrictVec; }

private:
	ObjectManager* objectmanager;
	HudManager* hudManager;
	Color background_color = Common::Dark_Slate_Green;
	bool level_change = false;
	std::string m_nextLevel;
	bool isPaused = false;

private:
	bool key_released_reset = false; //When level change, reset
	vector2 pressDirection = vector2{ 0,0 };
	vector2 playerRestrictedVec = vector2{ 1,1 };
	float player_velocity = 10.f;
};

template<typename T>
inline T * State::BuildObjectTemplate(std::string p_name, MeshPolygonType type)
{
	T* newObj =  objectmanager->AddObjectTemplate<T>(p_name);
	if(type == MeshPolygonType::Box)
		newObj->SetMesh(mesh::CreateBox(1.0f));
	if(type == MeshPolygonType::Circle)
		newObj->SetMesh(mesh::CreateCircle(1.0f));
	newObj->GetMesh().mesh_polygon_type = type;
	return newObj;
}

template<typename T>
inline T * State::BuildTextureTemplate(std::string p_name, MeshPolygonType type)
{
	T* newObj = objectmanager->AddObjectTemplate<T>(p_name);
	if (type == MeshPolygonType::Box)
		newObj->SetMesh(mesh::CreateTextureBox(1.0f));
	newObj->GetMesh().mesh_polygon_type = type;
	return newObj;
}