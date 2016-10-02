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
	//�������� ������ �� ���������� �������
	colorA = MINTRTHRESHOLD(colorA); colorA = MAXTRTHRESHOLD(colorA);
	colorB = MINTRTHRESHOLD(colorB); colorB = MAXTRTHRESHOLD(colorB);
	colorC = MINTRTHRESHOLD(colorC); colorC = MAXTRTHRESHOLD(colorC);
	Size = CHECKSIZE(Size); 

	CTriangle *pTriangle = new CTriangle(Size);

	pTriangle->SetColorABC(colorA,colorB,colorC);
	pTriangle->Create(InterpolationType::BARYCENTRIC); //�������� ����� ����� ������������ 
	FigureList.push_back(pTriangle);				   //� �������������  �� ������ ���������������� ���������

	pTriangle = new CTriangle(Size);

	pTriangle->SetColorABC(colorA,colorB,colorC);
	pTriangle->Create(InterpolationType::LINEAR); //�������� ����� ������ ������������ c �������� �������������
	FigureList.push_back(pTriangle);

}
void CGraphicApplication::Draw()
{
	for(auto it = FigureList.begin();it!= FigureList.end();it++){
		(*it)->Draw();
	}
}
