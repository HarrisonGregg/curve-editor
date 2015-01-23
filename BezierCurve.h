#include "Freeform.h"

class BezierCurve : public Freeform
{
public:
	void setColor()
	{
		glColor3ub( 55, 255, 255 ); // Cyan 
	}

	static float bernstein(int i, int n, double t) {
		if(n==1){
			if(i==0) return 1-t;
			if(i==1) return t;
			return 0;
		}
		if(i < 0 || i > n) return 0;
		return (1-t) * bernstein(i, n-1, t)
					+t*bernstein(i-1, n-1, t);
	}
	
	static float bernsteinDerivative(int i, int n, double t) {
		if(n==1){
			if(i==0) return -1;
			if(i==1) return 1;
			return 0;
		}
		if(i < 0 || i > n) return 0;
		return -t*bernstein(i, n-1, t)
					+(1-t) * bernsteinDerivative(i, n-1, t)
					+bernstein(i-1, n-1, t)
					+t*bernsteinDerivative(i-1, n-1, t);
	}

	static float bernsteinSecondDerivative(int i, int n, double t) {
		if(n==1){
			return 0;
		}
		if(i < 0 || i > n) return 0;
		return 		
					-bernstein(i, n-1, t)
					-t*bernsteinDerivative(i, n-1, t)
					-bernsteinDerivative(i, n-1, t)
					+(1-t) * bernsteinSecondDerivative(i, n-1, t)
					+bernsteinSecondDerivative(i-1, n-1, t)
					+bernsteinDerivative(i-1, n-1, t);
					+t*bernsteinSecondDerivative(i-1, n-1, t);
	}

	float2 getPoint(float t)
	{
		float2 r = float2(0.0, 0.0);
		
		int n = controlPoints.size();
		
		for(int i = 0; i < n; i++)
		{
			r += controlPoints[i]*bernstein(i, n-1, t);
		}
		
		return r;
	}

	float2 getDerivative(float t)
	{
		float2 d = float2(0.0, 0.0);
		
		int n = controlPoints.size();
		
		for(int i = 0; i < n; i++)
		{
			d += controlPoints[i]*bernsteinDerivative(i, n-1, t);
		}
		
		return d;
	}

	float2 getSecondDerivative(float t)
	{
		float2 d2 = float2(0.0, 0.0);
		
		int n = controlPoints.size();
		
		for(int i = 0; i < n; i++)
		{
			d2 += controlPoints[i]*bernsteinSecondDerivative(i, n-1, t);
		}
		
		return d2;
	}
};
