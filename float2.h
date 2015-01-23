#ifndef __ComputerGraphics__float2__
#define __ComputerGraphics__float2__

#include <stdlib.h>
#include <iostream>
#include <math.h>

class float2{
	public:
		float x;
		float y;

		float2():x(0.0),y(0.0){}

		float2(float x, float y):x(x),y(y){}
		
		float2 operator+(float2 b) const;

		float2 operator-(float2 b) const;

		float2 operator*(float2 b) const;
		
		float2 operator*(float s) const;
		
		float2 operator/(float s) const;

		float2 operator/(float2 b) const;

		void operator*=(float s);
		
		void operator+=(float2 b);

		void operator/=(float s);

		void operator*=(float2 s);
		
		float lengthSquared() const;

		float length() const;
		
		float2 normalize();
		
		static float2 random();

		static float2 random(float minX, float maxX, float minY, float maxY);
};

#endif
