#include "AntiEnemy.hpp"

AntiEnemy::AntiEnemy()
{
	m_objectType = ObjectType::antienemy;
}

bool AntiEnemy::Update()
{
	bool result = Object::Update();
	return result;
}

void AntiEnemy::CollideWithType(ObjectType type)
{
	if (type == ObjectType::enemy)
	{
		liveLeft -= 1;
		ChangeTexture();
	}
	if (liveLeft < 0) IsDelete = true;
}

void AntiEnemy::AddTexture(std::string path, vector2 size)
{
	texturePaths.push_back(path);
	if (size == vector2(0, 0))
		sizeChange.push_back(GetTransform().GetScale());
	else
		sizeChange.push_back(size);
}

void AntiEnemy::ChangeTexture()
{
	if (GetMesh().texture == nullptr) return;
	currentTexture++;
	if (texturePaths.size() <= currentTexture) return;
	GetMesh().texture->ChangeTexture((texturePaths.at(currentTexture)).c_str());
	GetTransform().SetScale(sizeChange.at(currentTexture));
}
