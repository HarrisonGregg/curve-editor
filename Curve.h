#ifndef __ComputerGraphics__Curve__
#define __ComputerGraphics__Curve__

#include <stdlib.h>
#include <math.h>

const float PI = 3.14159265;

class Curve
{
public:
	virtual float2 getPoint(float t)=0;

	virtual float2 getDerivative(float t)
	{
		float2 d = float2(0.0, 0.0);
				
		return d;
	}

	virtual float2 getSecondDerivative(float t)
	{
		float2 d2 = float2(0.0, 0.0);
		
		return d2;
	}

	virtual void draw(){
		for(float t = 0.0; t < 1.0; t+= 0.001){
			float2 v = getPoint(t);
			glVertex2f(v.x, v.y);
		}
	};
	
	void drawTracker(float t){
		float2 v = getPoint(t);

		float trackerWidth = 2.5;
		float trackerHeight = 2.5;
			
		glColor3d(0.0, 0.0, 1.0);
		glBegin(GL_TRIANGLE_STRIP);
			glVertex2d(v.x-trackerWidth, v.y-trackerHeight);
			glVertex2d(v.x+trackerWidth, v.y-trackerHeight);
			glVertex2d(v.x-trackerWidth, v.y+trackerHeight);
			glVertex2d(v.x+trackerWidth, v.y+trackerHeight);
		glEnd();
		
		float2 v2 = v + getDerivative(t);
			glBegin(GL_LINE_STRIP);
			glVertex2f(v.x, v.y);
			glVertex2f(v2.x, v2.y);
		glEnd();		

		float2 v3 = v + getSecondDerivative(t);
		glColor3d(0.0, 1.0, 0.0);	
		glBegin(GL_LINE_STRIP);
			glVertex2f(v.x, v.y);
			glVertex2f(v3.x, v3.y);
		glEnd();		
	}
};

#endif
