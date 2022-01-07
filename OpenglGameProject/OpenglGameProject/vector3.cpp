#include "vector3.hpp"

vector3::vector3(float fx, float fy, float fz)
{
	x = fx;
	y = fy;
	z = fz;
}

void vector3::operator+=(const vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
}

void vector3::operator-=(const vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;

}
void vector3::operator*=(float scale)
{
	x *= scale;
	y *= scale;
	z *= scale;
}
void vector3::operator/=(float divisor)
{
	x /= divisor;
	y /= divisor;
	z /= divisor;

}

vector3 vector3:: operator-() const
{
	vector3 temp = *this;
	temp.x *= -1;
	temp.y *= -1;
	temp.z *= -1;
	return temp;
}

vector3 vector3::operator+(const vector3& v) const
{
	vector3 temp = *this;
	temp.x = x + v.x;
	temp.y = y + v.y;
	temp.z = z + v.z;
	return temp;
}
vector3 vector3::operator-(const vector3& v) const
{
	vector3 temp = *this;
	temp.x = x - v.x;
	temp.y = y - v.y;
	temp.z = z - v.z;
	return temp;
}
vector3 vector3::operator*(float scale) const
{
	vector3 temp = *this;
	temp.x = x * scale;
	temp.y = y * scale;
	temp.z = z * scale;
	return temp;
}
vector3 vector3::operator/(float divisor) const
{
	vector3 temp = *this;
	temp.x = x / divisor;
	temp.y = y / divisor;
	temp.z = z / divisor;
	return temp;
}

bool vector3::operator==(const vector3& v) const
{
	if (x == v.x&&y == v.y&&z == v.z)
		return true;
	return false;

}
bool vector3::operator!=(const vector3& v) const
{
	if (x == v.x&&y == v.y&&z == v.z)
		return false;
	return true;
}

vector3 operator*(float scale, const vector3& v)
{
	vector3 temp;
	temp.x = scale * v.x;
	temp.y = scale * v.y;
	temp.z = scale * v.z;

	return temp;
}

float dot(vector3 a, vector3 b)
{
	float temp;
	temp = a.x * b.x + a.y * b.y + a.z * b.z;
	return temp;

}
vector3 cross(vector3 a, vector3 b)
{
	vector3 temp;
	temp.x = a.y * b.z - a.z * b.y;
	temp.y = a.z * b.x - a.x * b.z;
	temp.z = a.x * b.y - a.y * b.x;

	return temp;
}