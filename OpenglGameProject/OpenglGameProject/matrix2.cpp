#include "matrix2.hpp"


matrix2::matrix2(column first_column, column second_column)
{
	elements[0][0] = first_column.x;
	elements[0][1] = first_column.y;
	elements[1][0] = second_column.x;
	elements[1][1] = second_column.y;
}
matrix2::matrix2(float column0_row0, float column0_row1, float column1_row0, float column1_row1)
{
	elements[0][0] = column0_row0;
	elements[0][1] = column0_row1;
	elements[1][0] = column1_row0;
	elements[1][1] = column1_row1;
}

float matrix2::operator()(int column, int row) const
{
	return elements[column][row];
}

float& matrix2::operator()(int column, int row)
{
	return elements[column][row];
}

matrix2& matrix2::operator*=(matrix2 m)
{
	this->elements[0][0] = this->elements[0][0] * m.elements[0][0] + this->elements[1][0] * m.elements[0][1];
	this->elements[1][0] = this->elements[0][0] * m.elements[1][0] + this->elements[1][0] * m.elements[1][1];
	this->elements[0][1] = this->elements[0][1] * m.elements[0][0] + this->elements[1][1] * m.elements[0][1];
	this->elements[1][1] = this->elements[1][1] * m.elements[1][0] + this->elements[1][1] * m.elements[1][1];

	return *this;
}
matrix2 matrix2::operator*(matrix2 m) const
{
	matrix2 temp;
	temp.elements[0][0] = this->elements[0][0] * m.elements[0][0] + this->elements[1][0] * m.elements[0][1];
	temp.elements[1][0] = this->elements[0][0] * m.elements[1][0] + this->elements[1][0] * m.elements[1][1];
	temp.elements[0][1] = this->elements[0][1] * m.elements[0][0] + this->elements[1][1] * m.elements[0][1];
	temp.elements[1][1] = this->elements[1][1] * m.elements[1][0] + this->elements[1][1] * m.elements[1][1];

	return temp;
}

vector2 matrix2::operator*(column v) const
{
	vector2 vec;
	vec.x = this->elements[0][0] * v.x + this->elements[0][1] * v.y;
	vec.y = this->elements[1][0] * v.x + this->elements[1][1] * v.y;
	return vec;
}

namespace Matrix2
{
	matrix2 transpose(matrix2 m)
	{
		matrix2 temp;
		temp = { m.elements[1][1],-m.elements[1][0],-m.elements[0][0],m.elements[0][1] };
		return temp;
	}
	matrix2 build_rotation(float angle_in_radians)
	{
		matrix2 temp;
		temp = { cos(angle_in_radians),sin(angle_in_radians),-sin(angle_in_radians),cos(angle_in_radians) };
		return temp;
	}
	matrix2 build_identity()
	{
		matrix2 temp;
		temp = { 1,0,0,1 };
		return temp;
	}
	matrix2 build_scale(float scale)
	{
		matrix2 temp;
		temp = { scale ,0,scale,0 };
		return temp;
	}
	matrix2 build_scale(float scale_x, float scale_y)
	{
		matrix2 temp;
		temp = { scale_x ,0,scale_y,0 };
		return temp;
	}
	float determinate(matrix2 m)
	{
		float determin;
		determin = m.elements[0][0] * m.elements[1][1] - m.elements[0][1] * m.elements[1][0];
		return determin;
	}
	matrix2 invert(matrix2 m)
	{
		matrix2 temp;
		temp = { determinate(m)*m.elements[1][1],determinate(m)*-m.elements[1][0],
				determinate(m)*-m.elements[0][0],determinate(m)*m.elements[0][1] };
		return temp;
	}
}