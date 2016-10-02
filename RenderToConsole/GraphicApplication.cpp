#include "stdafx.h"
#include "Triangle.h"

CGraphicApplication::CGraphicApplication()
{
}

CGraphicApplication::~CGraphicApplication()
{
	for(auto it = FigureList.begin();it!= FigureList.end();it++){
		delete (*it);
	}

	FigureList.clear();
}
void CGraphicApplication::AddTriangle(int Size,int colorA,int colorB,int colorC)
{
	//ѕроверка выхода за допустимые пределы
	colorA = MINTRTHRESHOLD(colorA); colorA = MAXTRTHRESHOLD(colorA);
	colorB = MINTRTHRESHOLD(colorB); colorB = MAXTRTHRESHOLD(colorB);
	colorC = MINTRTHRESHOLD(colorC); colorC = MAXTRTHRESHOLD(colorC);
	Size = CHECKSIZE(Size); 

	CTriangle *pTriangle = new CTriangle(Size);

	pTriangle->SetColorABC(colorA,colorB,colorC);
	pTriangle->Create(InterpolationType::BARYCENTRIC); //создадим буфер верши треугольника 
	FigureList.push_back(pTriangle);				   //с интерпол€цией  на основе барицентрических координат

	pTriangle = new CTriangle(Size);

	pTriangle->SetColorABC(colorA,colorB,colorC);
	pTriangle->Create(InterpolationType::LINEAR); //создадим буфер вершин треугольника c линейной интерпол€цией
	FigureList.push_back(pTriangle);

}
void CGraphicApplication::Draw()
{
	for(auto it = FigureList.begin();it!= FigureList.end();it++){
		(*it)->Draw();
	}
}
