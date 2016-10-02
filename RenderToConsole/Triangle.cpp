#include "StdAfx.h"
#include "Triangle.h"


CTriangle::CTriangle()
{
	mSize = 15;
	mInterpType = BARYCENTRIC;
	
}
CTriangle::CTriangle(int Size)
{
	mA.x = 0;
	mA.y = 0;
	mB.x = Size;
	mB.y = Size;
	mC.x = 0;
	mC.y = Size;

	mSize = Size;

	mInterpType = BARYCENTRIC;
}

CTriangle::~CTriangle()
{

}

void CTriangle::Create(InterpolationType IType)
{
	 _Vertex Vert;

	 mInterpType = IType;

	for(int OY = 0;OY<=mSize;OY++){
		for(int OX = 0; OX < OY; OX++){
				Vert.x = OX; 
				Vert.y = OY;
				switch(IType){
				case InterpolationType::BARYCENTRIC:
					BarycentricCoordInterpolate(Vert);
				break;
				case InterpolationType::LINEAR:
					LinearInterpolate(Vert);
				break;
				};
				PointList.push_back(Vert);
			}
	}
}

void CTriangle::SetColorABC(int colorA,int colorB,int colorC)
{	
	mA.color = colorA;
	mB.color = colorB;
	mC.color = colorC;
}

void CTriangle::LinearInterpolate(_Vertex &Vertex)
{
	int  CurentLength = (int)sqrt(Vertex.x*Vertex.x + Vertex.y*Vertex.y);
	int  PointALength = (int)sqrt(mA.x*mA.x + mA.y*mA.y);
	int  PointBLength = (int)sqrt(mB.x*mB.x + mB.y*mB.y);
	int  PointCLength = (int)sqrt(mC.x*mC.x + mC.y*mC.y);

	////f(X1)+( f(X2) - f(X1) )*(X - X1)/(X2 - X1)
	int c1  = mA.color + ( mB.color - mA.color )*(CurentLength - PointALength)/(PointBLength - PointALength);//AB
	int c2  = mC.color + ( mA.color - mC.color )*(CurentLength - PointCLength)/(PointALength - PointCLength);//CA
	Vertex.color = (c1+c2)/2;
	
	// ‘ункци€ хорошо работает с целочисленными типами но не подходит дл€ треугольника и потому работает не корректно 

}

void CTriangle::BarycentricCoordInterpolate(_Vertex &Vertex)
{

	//интерпол€ци€ атрибутов вершин на основе барицентрических координат

	int l1 = (((mB.y - mC.y) * (Vertex.x	- mC.x) + (mC.x - mB.x) * (Vertex.y	- mC.y))*2) / // „ислитель умножен на 2 чтобы избежать нулевого значени€
             ((mB.y  - mC.y)  * (mA.x		- mC.x) + (mC.x - mB.x) * (mA.y		- mC.y));	  // 
    int l2 = (((mC.y - mA.y) * (Vertex.x	- mC.x) + (mA.x - mC.x) * (Vertex.y	- mC.y))*2) / // „ислитель умножен на 2 чтобы избежать нулевого значени€
             ((mB.y  - mC.y)  * (mA.x		- mC.x) + (mC.x - mB.x) * (mA.y		- mC.y));
    int l3 = 1 - l1 - l2;

	if(l1 >= 0 && l1 <= 1 && l2 >= 0 && l2 <= 1 && l3 >= 0 && l3 <= 1){
		Vertex.color = l1 *mA.color + l2*mB.color  + l3*mC.color ;
    }
	
	//‘ункци€ работает точнее с типами с плавающей зап€той
	
}

void CTriangle::Draw()
{

	int Y = 1;

	for(UINT i = 0;i<PointList.size();i++){
		if(PointList[i].x != -1){
			if(PointList[i].y != Y){	
				cout <<endl;
				Y++;
			}
			cout <<" "<< PointList[i].color;
		}
	}
	cout <<endl;

	switch (mInterpType)
	{
	case LINEAR:
		cout <<"Linear Interpolation "<<endl;
		break;
	case BARYCENTRIC:
		cout <<"Barycentric Interpolation "<<endl;
		break;
	default:
		break;
	}

	

}
