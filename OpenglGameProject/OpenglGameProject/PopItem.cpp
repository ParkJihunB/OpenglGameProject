#include "PopItem.hpp"

PopItem::PopItem()
{
	m_objectType = ObjectType::popitem;
}

bool PopItem::Update()
{
	bool result = Object::Update();
	return result;
}

void PopItem::CollideWithType(ObjectType type)
{
	if (type == ObjectType::player) IsDelete = true;
	if (type == ObjectType::antipop) IsDelete = true;
}
