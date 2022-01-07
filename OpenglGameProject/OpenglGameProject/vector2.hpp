#pragma once
#include <math.h>
#include <iostream>


struct vector2
{
	float x = 0.0f, y = 0.0f;

	vector2() = default;
	vector2(float x_, float y_);
	vector2(float value);

	void operator+=(const vector2& vec);
	void operator-=(const vector2& vec);
	void operator*=(float scale);
	void operator/=(float divisor);

	vector2 operator-() const;

	vector2 operator+(const vector2& vec) const;
	vector2 operator-(const vector2& vec) const;
	vector2 operator*(float scale) const;
	vector2 operator/(float divisor) const;

	bool operator==(const vector2& vec) const;
	bool operator!=(const vector2& vec) const;


};

vector2 operator*(float scale, const vector2& vec);
float magnitude(vector2& vec);
vector2 normalize(const vector2& vec);
float dot(vector2 lhs, vector2 rhs);
float distance_between(vector2 lhs, vector2 rhs);