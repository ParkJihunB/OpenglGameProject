#pragma once
#include "affine2d.hpp"
#include "vector3.hpp"
#include "vector2.hpp"

class Transform
{
public:
	Transform() = default;
	affine2d& GetModelToWorld() const;


	float GetDepth() const;
	void SetDepth(float new_depth);

	vector2 GetTranslation() const;
	void SetTranslation(const vector2& new_translation);

	vector2 GetScale() const;
	void SetScale(const vector3& new_scale);
	void SetScale(const vector2& new_scale);

	float GetRotation() const;
	void SetRotation(float new_rotation);


private:
	vector2 translation{};
	vector2 scale{ 1.0f,1.0f };
	float rotation = 0.0f;
	float depth = 0.0f;
	mutable affine2d model_to_world{ 1, 0, 0, 0, 1, 0, 0, 0, 1 };
};