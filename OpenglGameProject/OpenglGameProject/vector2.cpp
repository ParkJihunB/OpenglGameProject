#include "vector2.hpp"


vector2::vector2(float x_, float y_)
{
	x = x_;
	y = y_;
}

vector2::vector2(float value)
{
	x = value;
	y = value;
}

vector2 vector2::operator+(const vector2 & vec) const
{
	vector2 temp = *this;
	temp.x = x + vec.x;
	temp.y = y + vec.y;
	return temp;
}

void vector2::operator+=(const vector2 & vec)
{
	x += vec.x;
	y += vec.y;
}

void vector2::operator-=(const vector2 & vec)
{
	x -= vec.x;
	y -= vec.y;
}

vector2 vector2::operator-(const vector2 & vec) const
{
	vector2 temp;
	temp.x = x - vec.x;
	temp.y = y - vec.y;
	return temp;
}

vector2 vector2::operator-() const
{
	vector2 temp = *this;
	temp.x *= -1.f;
	temp.y *= -1.f;
	return temp;
}

void vector2::operator*=(float scale)
{
	x *= scale;
	y *= scale;
}

vector2 vector2::operator*(float scale) const
{
	vector2 temp;
	temp.x = x * scale;
	temp.y = y * scale;
	return temp;
}

vector2 operator*(float scale, const vector2 & vec)
{
	vector2 temp;
	temp.x = vec.x * scale;
	temp.y = vec.y * scale;
	return temp;
}


void vector2::operator/=(float divisor)
{
	x = x / divisor;
	y = y / divisor;
}

vector2 vector2::operator/(float divisor) const
{
	vector2 temp;
	temp.x = x / divisor;
	temp.y = y / divisor;
	return temp;
}

bool vector2::operator==(const vector2 & vec) const
{
	if (x == vec.x && y == vec.y)
		return true;
	return false;
}


bool vector2::operator!=(const vector2 & vec) const
{
	if (*this == vec)
		return false;
	return true;

}

float magnitude(vector2& vec)
{
	float vec_magnitude;
	vec_magnitude = sqrt(vec.x * vec.x + vec.y * vec.y);
	return vec_magnitude;
}

vector2 normalize(const vector2 & vec)
{
	vector2 normalized = vec;
	float length = sqrt(vec.x * vec.x + vec.y * vec.y);
	normalized /= length;
	return normalized;
}

float dot(vector2 lhs, vector2 rhs)
{
	float dot;
	dot = lhs.x * rhs.x + lhs.y * rhs.y;
	return dot;
}

float distance_between(vector2 lhs, vector2 rhs)
{
	float distance;
	distance = sqrt((lhs.x - rhs.x) * (lhs.x - rhs.x)
		+ (lhs.y - rhs.y) * (lhs.y - rhs.y));
	return distance;
}