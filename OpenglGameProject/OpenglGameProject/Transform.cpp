#include "Transform.hpp"

affine2d& Transform::GetModelToWorld() const
{
	model_to_world = { 1,0,0,0,1,0,0,0,1 };
	model_to_world = build_translation(translation.x, translation.y)
		*build_rotation(rotation)
		*build_scale(scale.x, scale.y);

	return model_to_world;
}


float Transform::GetDepth() const { return depth; }

void Transform::SetDepth(float new_depth)
{
	depth = new_depth;
}

vector2 Transform::GetTranslation() const { return translation; }

void Transform::SetTranslation(const vector2& new_translation)
{
	translation = new_translation;
}

vector2 Transform::GetScale() const { return scale; }

void Transform::SetScale(const vector3& new_scale)
{
	scale = { new_scale.x,new_scale.y };
}

void Transform::SetScale(const vector2& new_scale)
{
	scale = new_scale;
}

float Transform::GetRotation() const { return rotation; }

void Transform::SetRotation(float new_rotation)
{
	rotation = new_rotation;
}
