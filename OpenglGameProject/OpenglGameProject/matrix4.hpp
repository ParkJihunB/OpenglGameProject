#pragma once
#include "vector4.hpp"

class matrix4
{
public:
	using column = vector4;
	static constexpr int rank = 4;
	float elements[rank][rank] = { { 0.0f, 0.0f, 0.0f, 0.0f },{ 0.0f, 0.0f, 0.0f, 0.0f }
									,{ 0.0f, 0.0f, 0.0f, 0.0f },{ 0.0f, 0.0f, 0.0f, 0.0f } };
	matrix4() = default;
	matrix4(column first_column, column second_column, column third_column, column forth_column);

	matrix4(float column0_row0, float column0_row1, float column0_row2, float column0_row3,
			float column1_row0, float column1_row1, float column1_row2, float column1_row3,
			float column2_row0, float column2_row1, float column2_row2, float column2_row3,
			float column3_row0, float column3_row1, float column3_row2, float column3_row3);
private:

};

matrix4 build_ortho(float left, float right, float bottom, float top);

