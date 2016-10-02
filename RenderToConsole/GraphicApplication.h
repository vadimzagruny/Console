#pragma once
using namespace std;
#include <windows.h>
#include "Figure.h"
#include <vector>

#define MINTRTHRESHOLD(A) A<0?0:A
#define MAXTRTHRESHOLD(A) A>9?9:A

#define CHECKSIZE(A) A>64?64:A

enum InterpolationType{
	LINEAR		= 0,
	BARYCENTRIC = 1,
};

class CGraphicApplication
{

	vector<CFigure*>FigureList;

public:

	void AddTriangle(int Size,int colorA,int colorB,int colorC);
	void Draw();

	CGraphicApplication(void);
	~CGraphicApplication(void);
};

