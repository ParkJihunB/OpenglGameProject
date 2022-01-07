#include "matrix4.hpp"

matrix4::matrix4(column first_column, column second_column, column third_column, column forth_column)
{
	elements[0][0] = first_column.x;
	elements[0][1] = first_column.y;
	elements[0][2] = first_column.z;
	elements[0][3] = first_column.w;

	elements[1][0] = second_column.x;
	elements[1][1] = second_column.y;
	elements[1][2] = second_column.z;
	elements[1][3] = second_column.w;

	elements[2][0] = third_column.x;
	elements[2][1] = third_column.y;
	elements[2][2] = third_column.z;
	elements[2][3] = third_column.w;

	elements[3][0] = forth_column.x;
	elements[3][1] = forth_column.y;
	elements[3][2] = forth_column.z;
	elements[3][3] = forth_column.w;
}

matrix4::matrix4(float column0_row0, float column0_row1, float column0_row2, float column0_row3, 
				float column1_row0, float column1_row1, float column1_row2, float column1_row3, 
				float column2_row0, float column2_row1, float column2_row2, float column2_row3, 
				float column3_row0, float column3_row1, float column3_row2, float column3_row3)
{
	elements[0][0] = column0_row0;
	elements[0][1] = column0_row1;
	elements[0][2] = column0_row2;
	elements[0][3] = column0_row3;

	elements[1][0] = column1_row0;
	elements[1][1] = column1_row1;
	elements[1][2] = column1_row2;
	elements[1][3] = column1_row3;

	elements[2][0] = column2_row0;
	elements[2][1] = column2_row1;
	elements[2][2] = column2_row2;
	elements[2][3] = column2_row3;

	elements[3][0] = column3_row0;
	elements[3][1] = column3_row1;
	elements[3][2] = column3_row2;
	elements[3][3] = column3_row3;
}


matrix4 build_ortho(float left, float right, float bottom, float top)
{
	matrix4 temp;
	temp.elements[0][0] = 2.f / (right - left);
	temp.elements[1][1] = 2.f / (top - bottom);
	temp.elements[2][2] = -1.f;
	temp.elements[3][0] = -(right + left) / (right - left);
	temp.elements[3][1] = -(top + bottom) / (top - bottom);
	return temp;
}
