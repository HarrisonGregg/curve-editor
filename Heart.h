#include <stdlib.h>
#include <math.h>

#include "Curve.h"

class Heart : public Curve
{
public:
	float x0;
	float y0;
	float r;
	
	Heart(float x0, float y0, float r):x0(x0),y0(y0),r(r)
	{
		trackerWidth = 0.05;
		trackerHeight = 0.05;
	};
	
	float2 getPoint(float t);

	float2 getDerivative(float t);
	float2 getSecondDerivative(float t);
};
