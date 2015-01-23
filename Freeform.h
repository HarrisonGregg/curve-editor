#ifndef __ComputerGraphics__freeform__
#define __ComputerGraphics__freeform__

#include <vector>
#include "Curve.h"
#include "float2.h"

class Freeform : public Curve
{
public:
	std::vector<float2> controlPoints;
	float2 offset;

	virtual void setColor()=0;

	virtual void addControlPoint(float2 p)
	{
		controlPoints.push_back(p-offset);
	}
	
	virtual void reset()
	{
		controlPoints.erase(controlPoints.begin(),controlPoints.begin()+controlPoints.size());
	}

	virtual void drawFreeform(bool selected, bool filled)
	{
		glPushMatrix();
		glTranslatef(offset.x, offset.y, 0);
		if(selected){
			glColor3ub( 0, 0, 255 ); // Blue
		} else {
			setColor();
		}
		glLineWidth(2*(1+selected));
		if(filled){
			glBegin(GL_TRIANGLE_FAN);
		} else {
			glBegin(GL_LINE_STRIP);
		}
		draw();
		glEnd();
		glPopMatrix();
	}
	
	void drawControlPoints(bool selected){
		float width = 2.5;
		float height = 2.5;

		if(selected){
			glColor3ub( 0, 0, 255 );
		} else {
			setColor();
		}

		glPushMatrix();
		glTranslatef(offset.x, offset.y, 0);
		for(float2 &v : controlPoints){
			glBegin(GL_TRIANGLE_STRIP);
				glVertex2d(v.x-width, v.y-height);
				glVertex2d(v.x+width, v.y-height);
				glVertex2d(v.x-width, v.y+height);
				glVertex2d(v.x+width, v.y+height);
			glEnd();
		}
		glPopMatrix();
	}
};

#endif
