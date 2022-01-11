#include "State.hpp"

void State::Load()
{
	level_change = false;
	objectmanager = new ObjectManager();
	hudManager = new HudManager();
	key_released_reset = true;
	std::cout << "State::State Load" << std::endl;
	std::cout << "State::Create new Object Manager" << std::endl;
}

void State::UnLoad()
{
	objectmanager->Quit();
	delete objectmanager;
	objectmanager = nullptr;
	std::cout << "State::Delete Object Manager" << std::endl;

	hudManager->Quit();
	delete hudManager;
	hudManager = nullptr;
	std::cout << "State::Delete HUD Manager" << std::endl;
}

void State::ChangeLevel(std::string p_nextLevel)
{
	m_nextLevel = p_nextLevel;
	level_change = true;
	key_released_reset = true;
	std::cout << "Ready to change state" << std::endl << std::endl;
}

void State::SetPause(bool pause)
{
	isPaused = pause;
	if(pause) key_released_reset = true;
}

Object * State::BuildBox(std::string p_name, float p_scale, Color p_color, vector2 p_trans)
{
	objectmanager->AddObject(p_name);
	objectmanager->GetObject(p_name);
	objectmanager->GetObject(p_name)->SetMesh(mesh::CreateBox(1.0f));
	objectmanager->GetObject(p_name)->SetColor(p_color);
	objectmanager->GetObject(p_name)->SetScale(p_scale);
	objectmanager->GetObject(p_name)->SetTranslation(p_trans);
	return objectmanager->GetObject(p_name);
}

Object * State::BuildCircle(std::string p_name, float p_scale, Color p_color, vector2 p_trans)
{
	objectmanager->AddObject(p_name);
	objectmanager->GetObject(p_name);
	objectmanager->GetObject(p_name)->SetMesh(mesh::CreateCircle());
	objectmanager->GetObject(p_name)->SetColor(p_color);
	objectmanager->GetObject(p_name)->SetScale(p_scale);
	objectmanager->GetObject(p_name)->SetTranslation(p_trans);
	//objectmanager->GetObject(p_name)->SetInitPosiiton(p_trans);
	objectmanager->GetObject(p_name)->GetMesh().mesh_polygon_type = MeshPolygonType::Circle;
	return objectmanager->GetObject(p_name);
}

Object* State::BuildCircle(std::string p_name, float p_scale, Color p_color, vector2 p_trans, ObjectType p_type)
{
	objectmanager->AddObject(p_name);
	objectmanager->GetObject(p_name);
	objectmanager->GetObject(p_name)->SetMesh(mesh::CreateCircle());
	objectmanager->GetObject(p_name)->SetColor(p_color);
	objectmanager->GetObject(p_name)->SetScale(p_scale);
	objectmanager->GetObject(p_name)->SetTranslation(p_trans);
	//objectmanager->GetObject(p_name)->SetInitPosiiton(p_trans);
	objectmanager->GetObject(p_name)->GetMesh().mesh_polygon_type = MeshPolygonType::Circle;
	//objectmanager->GetObject(p_name)->type = p_type;
	return objectmanager->GetObject(p_name);
}

Object* State::BuildLine(std::string p_name, vector2 start, vector2 end, Color p_color)
{
	objectmanager->AddObject(p_name);
	objectmanager->GetObject(p_name)->SetMesh(mesh::CreateLine(start, end));
	objectmanager->GetObject(p_name)->SetColor(p_color);
	objectmanager->GetObject(p_name)->GetMesh().mesh_polygon_type = MeshPolygonType::Line;
	return objectmanager->GetObject(p_name);
}

Text * State::BuildText(std::string p_name, std::string textData)
{
	hudManager->AddText(p_name, textData);
	return hudManager->GetText(p_name);
}

void State::PlayerMovement(Object * p_player)
{
	if (!objectmanager->IsPlayerAlive())
	{
		key_released_reset = true;
		return;
	}

	vector2 current_transform = p_player->GetTransform().GetTranslation();
	if (Input::IsKeyAnyPressed())
	{
		if (Input::IsKeyPressed(GLFW_KEY_W))
			pressDirection.y += 1.f* player_velocity;
		if (Input::IsKeyPressed(GLFW_KEY_S))
			pressDirection.y += -1.f* player_velocity;
		if (Input::IsKeyPressed(GLFW_KEY_A))
			pressDirection.x += -1.f* player_velocity;
		if (Input::IsKeyPressed(GLFW_KEY_D))
			pressDirection.x += 1.f* player_velocity;
	}

	if (Input::IsKeyAnyReleased())
	{
		if (Input::IsKeyReleased(GLFW_KEY_W))
			pressDirection.y += -1.f* player_velocity;
		if (Input::IsKeyReleased(GLFW_KEY_S))
			pressDirection.y += 1.f* player_velocity;
		if (Input::IsKeyReleased(GLFW_KEY_A))
			pressDirection.x += 1.f* player_velocity;
		if (Input::IsKeyReleased(GLFW_KEY_D))
			pressDirection.x += -1.f* player_velocity;
	}

	if (key_released_reset)
	{
		pressDirection = 0;
		key_released_reset = false;
	}
	
	pressDirection = vector2(pressDirection.x * playerRestrictedVec.x, pressDirection.y * playerRestrictedVec.y);
	p_player->AddVelocity(pressDirection);
}

