#include <stdlib.h>
#include "Freeform.h"

class Polyline : public Freeform
{
public:
	void setColor()
	{
		glColor3ub( 255, 0, 255 ); //Purple
	}

	//The inherited draw function works, but this draw function is faster
	void draw()
	{
		int n = controlPoints.size();
		for(float2 &v : controlPoints){
			glVertex2f(v.x, v.y);
		}
	}
	
	// I wrote this get point function so that trackers would work properly.  The 
	// function isn't used in this project, but I figured I would leave it.
	float2 getPoint(float t)
	{
		int n = controlPoints.size();
		if(n > 1){
			float totalLength = 0.0;
			
			for(int i = 0; i < n-1; i++){
				totalLength += (controlPoints[i]-controlPoints[i+1]).length();
			}
			
			float lengthSum = 0.0;
			for(int i = 0; i < n-1; i++){
				float segmentLength = (controlPoints[i+1]-controlPoints[i]).length();
				if(t >= lengthSum/totalLength && t <= (lengthSum + segmentLength)/totalLength){
					float2 difference = (controlPoints[i+1]-controlPoints[i]);
					return controlPoints[i]+difference*((t-lengthSum/totalLength)*totalLength/segmentLength);
				}
				lengthSum += segmentLength;
			}
			
			return controlPoints[0];
		}
		
		return float2(0,0);
	}
};
