#pragma once


class CFigure
{
protected:
	struct _Vertex
	{
		_Vertex(){
			x = y = color = 0;
		}
		int x,y;
		int color;
	};

	vector<_Vertex>PointList;

public:
	CFigure();
	~CFigure();

	virtual void BarycentricCoordInterpolate(_Vertex &Vertex) = 0;
	virtual void LinearInterpolate(_Vertex &Vertex) = 0;
	virtual void Draw() = 0;
};

