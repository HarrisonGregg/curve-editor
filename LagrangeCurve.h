#include "Freeform.h"

class LagrangeCurve : public Freeform
{
protected:
	std::vector<double> knots;
public:
	bool autoKnot; //Automatically weight all vertices equally

	LagrangeCurve()
	{
		autoKnot = true;
	};

	void setColor()
	{
		glColor3ub( 0, 255, 0 ); // Green
	}

	// This function could be used to create a Lagrange curve with non-uniform weights.
	void addControlPoint(float2 p, double w)
	{
		controlPoints.push_back(p);
		knots.push_back(w);
	}
	
	void addControlPoint(float2 p)
	{
		addControlPoint(p, 1.0);
	}
	
	void reset()
	{
		controlPoints.erase(controlPoints.begin(),controlPoints.begin()+controlPoints.size());
		knots.erase(knots.begin(),knots.begin()+knots.size());
	}
	
	float lagrange(int i, int n, double t) {
		double L = 1.0;
		
		for(int j = 0; j < n; j++){
			if(i!=j){
				if(autoKnot){
					L*= (t*(double)(n-1)-(double)j)/((double)i-(double)j);
				} else {
					L*= (t-knots[j])/(knots[i]-knots[j]);
				}
			}
		}
		
		return L;
	}

	float2 getPoint(float t)
	{
		float2 r = float2(0.0, 0.0);
		
		int n = controlPoints.size();
		
		for(int i = 0; i < n; i++)
		{
			r += controlPoints[i]*lagrange(i, n, t);
		}
		
		return r;
	}
};
