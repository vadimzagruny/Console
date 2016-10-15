#pragma once
#include "figure.h"
#include "FixedPointMAth.h"
using namespace std;
class CTriangle : public CFigure
{

	_Vertex mA;
	_Vertex mB;
	_Vertex mC;

	int mSize;

	InterpolationType mInterpType;


public:
	CTriangle();
	CTriangle(int Size);
	~CTriangle();

	void BarycentricCoordInterpolate(_Vertex &Vertex);
	void LinearInterpolate(_Vertex &Vertex);
	void Create(InterpolationType);
	void SetColorABC(int colorA,int colorB,int colorC);
	void Draw();
};

