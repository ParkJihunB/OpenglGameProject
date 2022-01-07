#pragma once
#include "vector2.hpp"

struct matrix2
{
public:
	using column = vector2;
	static constexpr int rank = 2;

public:
	float elements[rank][rank] = { { 0.0f, 0.0f },{ 0.0f, 0.0f } };

public:
	matrix2() = default;
	matrix2(column first_column, column second_column);
	matrix2(float column0_row0, float column0_row1, float column1_row0, float column1_row1);

	float operator()(int column, int row) const;
	float& operator()(int column, int row);

	matrix2& operator*=(matrix2 m);
	matrix2 operator*(matrix2 m) const;

	vector2 operator*(column v) const;
};

namespace Matrix2
{
	matrix2 transpose(matrix2 m);
	matrix2 build_rotation(float angle_in_radians);
	matrix2 build_identity();
	matrix2 build_scale(float scale);
	matrix2 build_scale(float scale_x, float scale_y);
	float determinate(matrix2 m);
	matrix2 invert(matrix2 m);
}