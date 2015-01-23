#include "Freeform.h"

class CatmullRomSpline : public Freeform
{
public:
	void setColor()
	{
		glColor3ub( 255, 0, 0 ); // Red
	}

	float2 tangent(int i)
	{
		int n = controlPoints.size();

		if (i > 0 && i < n-1) {
			return (controlPoints[i+1]-controlPoints[i-1])/(float)2.0;
		} else {
			return float2();
		}
	}

	float2 getPoint(float t)
	{
		int n = controlPoints.size()-1;
		int i = (int)(t*n);
		t = t*n-(float)i;

		float2 r = controlPoints[i]*(1-3*t*t+2*t*t*t)
 			   + controlPoints[i+1]*(3*t*t-2*t*t*t)
			   + tangent(i)*(t-2*t*t+t*t*t)
			   + tangent(i+1)*(-t*t+t*t*t);

		return r;
	}
};
