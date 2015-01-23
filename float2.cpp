#include <stdlib.h>
#include <math.h>
#include <iostream>

#include "float2.h"

using namespace std;

float2 float2::operator+(float2 b) const{
	return float2(x + b.x, y + b.y);
}

float2 float2::operator-(float2 b) const{
	return float2(x - b.x, y - b.y);
}

float2 float2::operator*(float2 b) const{
	return float2(x * b.x, y * b.y);
}

float2 float2::operator*(float s) const{
	return float2(x * s, y * s);
}

float2 float2::operator/(float s) const{
	return float2(x / s, y / s);
}

float2 float2::operator/(float2 b) const{
	return float2(x / b.x, y / b.y);
}

void float2::operator*=(float s) {
	x *= s;
	y *= s;
}

void float2::operator+=(float2 b) {
	x += b.x;
	y += b.y;
}

void float2::operator/=(float s) {
	x /= s;
	y /= s;
}

void float2::operator*=(float2 s) {
	x *= s.x;
	y *= s.y;
}

float float2::lengthSquared() const{
	return x*x + y*y;
}

float float2::length() const{
	return sqrtf(x*x + y*y);
}

float2 float2::normalize()
{
	*this /= length();
	return *this;
}

float2 float2::random()
{
	return float2(
		((float)rand() / RAND_MAX) * 2-1,
		((float)rand() / RAND_MAX) * 2-1);
}

float2 float2::random(float minX, float maxX, float minY, float maxY)
{
	return float2(
		((float)rand() / RAND_MAX) * (maxX-minX)+minX,
		((float)rand() / RAND_MAX) * (maxY-minY)+minY);
}
