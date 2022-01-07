#pragma once
#include "vector3.hpp"
#include "vector2.hpp"
#include <math.h>

struct affine2d
{
public:
	using column = vector3;
	static constexpr int rank = 3;

public:
	float elements[rank][rank] = { { 0.0f, 0.0f, 0.0f },{ 0.0f, 0.0f, 0.0f },{ 0.0f, 0.0f, 0.0f } };

public:
	affine2d() = default;
	affine2d(column first_column, column second_column, column third_column);

	affine2d(float column0_row0, float column0_row1, float column0_row2, float column1_row0, float column1_row1,
		float column1_row2, float column2_row0, float column2_row1, float column2_row2);

	float operator()(int column, int row)const;
	affine2d operator * (affine2d m) const;

};
vector2 operator*(affine2d a, vector2 v);
vector3 operator*(affine2d a, vector3 v);

affine2d build_rotation(float angle_in_radians);
affine2d build_identity();
affine2d build_scale(float scale);
affine2d build_scale(float scale_x, float scale_y);
affine2d build_translation(float translate_x, float translate_y);