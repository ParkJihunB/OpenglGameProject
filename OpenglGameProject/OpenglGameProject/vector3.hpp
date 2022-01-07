#pragma once
struct vector3
{
	float x = 0.0f, y = 0.0f, z = 0.0f;

	vector3() = default;
	vector3(float fx, float fy, float fz);

	void operator+=(const vector3& v);
	void operator-=(const vector3& v);
	void operator*=(float scale);
	void operator/=(float divisor);

	vector3 operator-() const;

	vector3 operator+(const vector3& v) const;
	vector3 operator-(const vector3& v) const;
	vector3 operator*(float scale) const;
	vector3 operator/(float divisor) const;

	bool operator==(const vector3& v) const;
	bool operator!=(const vector3& v) const;
};

vector3 operator*(float scale, const vector3& v);

float dot(vector3 a, vector3 b);
vector3 cross(vector3 a, vector3 b);