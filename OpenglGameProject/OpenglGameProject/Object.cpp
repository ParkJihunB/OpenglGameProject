#include "Object.hpp"

Object::Object(const Mesh& display_mesh, const Color &display_color)
{
	int size = static_cast<int>(display_mesh.points.size());

	for (int i = 0; i < size; i++)
		mesh.AddPoint(display_mesh.points[i]);

	mesh.AddColor(display_color);

	mesh.point_list_type = display_mesh.point_list_type;
}

bool Object::Update()
{
	if (type == ObjectType::pop)
	{
		if (IsCollide)
			return false;
	}
	if (IsDelete)
		return false;
	return true;
}

void Object::SetMesh(Mesh p_mesh)
{
	mesh = p_mesh;
}

void Object::SetColor(Color p_color)
{
	mesh.AddColor(p_color);
}

void Object::ChangeColor(Color p_color)
{
	mesh.ChangeColor(p_color);
}

void Object::SetTranslation(const vector2& p_position)
{
	//prev_position = transform.GetTranslation();
	transform.SetTranslation(p_position);
}

void Object::SetScale(const vector2 & p_scale)
{
	transform.SetScale(p_scale);
}

void Object::SetRotation(const float & p_rotation)
{
	transform.SetRotation(p_rotation);
}

void Object::SetDepth(const float & p_depth)
{
	transform.SetDepth(p_depth);
}

//void Object::SetCollidePos()
//{
//	if (IsCollide)
//		SetTranslation(prev_position);
//	else
//		prev_position = transform.GetTranslation();
//}

