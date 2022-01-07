#include "affine2d.hpp"

affine2d::affine2d(column first_column, column second_column, column third_column)
{
	elements[0][0] = first_column.x;
	elements[0][1] = first_column.y;
	elements[0][2] = first_column.z;
	elements[1][0] = second_column.x;
	elements[1][1] = second_column.y;
	elements[1][2] = second_column.z;
	elements[2][0] = third_column.x;
	elements[2][1] = third_column.y;
	elements[2][2] = third_column.z;

}
affine2d::affine2d(float column0_row0, float column0_row1, float column0_row2, float column1_row0, float column1_row1,
	float column1_row2, float column2_row0, float column2_row1, float column2_row2)
{
	elements[0][0] = column0_row0;
	elements[0][1] = column0_row1;
	elements[0][2] = column0_row2;
	elements[1][0] = column1_row0;
	elements[1][1] = column1_row1;
	elements[1][2] = column1_row2;
	elements[2][0] = column2_row0;
	elements[2][1] = column2_row1;
	elements[2][2] = column2_row2;
}

float affine2d::operator()(int column, int row) const
{
	return elements[column][row];
}


affine2d affine2d::operator*(affine2d m) const
{
	affine2d temp;
	temp.elements[0][0] = (this->elements[0][0] * m.elements[0][0]) + (this->elements[1][0] * m.elements[0][1]) + (this->elements[2][0] * m.elements[0][2]);
	temp.elements[1][0] = (this->elements[0][0] * m.elements[1][0]) + (this->elements[1][0] * m.elements[1][1]) + (this->elements[2][0] * m.elements[1][2]);
	temp.elements[2][0] = (this->elements[0][0] * m.elements[2][0]) + (this->elements[1][0] * m.elements[2][1]) + (this->elements[2][0] * m.elements[2][2]);
	temp.elements[0][1] = (this->elements[0][1] * m.elements[0][0]) + (this->elements[1][1] * m.elements[0][1]) + (this->elements[2][1] * m.elements[0][2]);
	temp.elements[1][1] = (this->elements[0][1] * m.elements[1][0]) + (this->elements[1][1] * m.elements[1][1]) + (this->elements[2][1] * m.elements[1][2]);
	temp.elements[2][1] = (this->elements[0][1] * m.elements[2][0]) + (this->elements[1][1] * m.elements[2][1]) + (this->elements[2][1] * m.elements[2][2]);
	temp.elements[0][2] = (this->elements[0][2] * m.elements[0][0]) + (this->elements[1][2] * m.elements[0][1]) + (this->elements[2][2] * m.elements[0][2]);
	temp.elements[1][2] = (this->elements[0][2] * m.elements[1][0]) + (this->elements[1][2] * m.elements[1][1]) + (this->elements[2][2] * m.elements[1][2]);
	temp.elements[2][2] = (this->elements[0][2] * m.elements[2][0]) + (this->elements[1][2] * m.elements[2][1]) + (this->elements[2][2] * m.elements[2][2]);

	return temp;
}

vector2 operator*(affine2d a, vector2 v)
{
	vector3 temp{ v.x,v.y,1.f };
	temp = a * temp;
	vector2 result{ temp.x,temp.y };
	return result;
}

//Please use column major ordering
/*
|00 10 20|  x   00*x + 10*y + 20*z
|01 11 21|  y = 01*x + 11*y + 21*z
|02 12 22|  z   02*x + 12*y + 22*z
*/
vector3 operator*(affine2d a, vector3 v)
{
	vector3 vec;
	vec.x = a.elements[0][0] * v.x + a.elements[1][0] * v.y + a.elements[2][0] * v.z;
	vec.y = a.elements[0][1] * v.x + a.elements[1][1] * v.y + a.elements[2][1] * v.z;
	vec.z = a.elements[0][2] * v.x + a.elements[1][2] * v.y + a.elements[2][2] * v.z;
	return vec;
}

affine2d build_rotation(float angle_in_radians)
{
	float cosn = static_cast<float>(cos(angle_in_radians));
	float sine = static_cast<float>(sin(angle_in_radians));
	affine2d temp;

	temp = { cosn, sine, 0, -sine, cosn,0,0,0,1 };
	return temp;
}

affine2d build_identity()
{
	affine2d temp;
	temp = { 1,0,0,0,1,0,0,0,1 };
	return temp;
}

affine2d build_scale(float scale)
{
	affine2d temp;
	temp = { scale,0,0,0,scale,0,0,0,1 };
	return temp;
}
affine2d build_scale(float scale_x, float scale_y)
{
	affine2d temp;
	temp = { scale_x, 0, 0, 0, scale_y, 0,0,0,1 };
	return temp;
}

affine2d build_translation(float translate_x, float translate_y)
{
	affine2d temp;
	temp = { 1,0,0,0,1,0,translate_x,translate_y,1 };
	return temp;
}