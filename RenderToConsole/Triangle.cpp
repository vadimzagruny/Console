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
	mB.x = Size-1;
	mB.y = Size-1;
	mC.x = 0;
	mC.y = Size-1;

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

	for(int OY = 0;OY<=mSize-1;OY++){
		for(int OX = 0; OX < (OY+1); OX++){
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
	// Линейная интерполяция для треугольника

	_Vertex CurrentPoint = Vertex;
	_Vertex tA,tB,tC;

	// Если текущая точка совпадает с одной из вершин треугольника то присвоить ей цвет вершины
	if(Vertex==mA){
		Vertex.color = mA.color;
		return;
	}
	if(Vertex==mB){
		Vertex.color = mB.color;
		return;
	}
	if(Vertex==mC){
		Vertex.color = mC.color;
		return;
	}

	// Переходим к математике с фиксированой точкой
	CurrentPoint.x = TOFIXEDPOINT(CurrentPoint.x);
	CurrentPoint.y = TOFIXEDPOINT(CurrentPoint.y);

	tA.x = TOFIXEDPOINT(mA.x); tA.color =  mA.color;
	tA.y = TOFIXEDPOINT(mA.y); tB.color =  mB.color;
	tB.x = TOFIXEDPOINT(mB.x); tC.color =  mC.color;
	tB.y = TOFIXEDPOINT(mB.y); tA.color = TOFIXEDPOINT( tA.color);
	tC.x = TOFIXEDPOINT(mC.x); tB.color = TOFIXEDPOINT( tB.color);
	tC.y = TOFIXEDPOINT(mC.y); tC.color = TOFIXEDPOINT( tC.color);

	int MatrixInv[3][3];
	int MatrixRes[3][3];

	int Matrix3x3[3][3] = {{tA.x,tB.x,tC.x},{tA.y,tB.y,tC.y},{FIXPOINTKOEFF,FIXPOINTKOEFF,FIXPOINTKOEFF}};
	int Matrix1x3[1][3] = {tA.color,tB.color,tC.color};
	int Matrix3x1[3][3] = {{CurrentPoint.x,0,0},{CurrentPoint.y,0,0},{FIXPOINTKOEFF,0,0}};
	
	//Вычисляем определитель матрицы
	int determinant = CFixedPointMAth::det(Matrix3x3);
	
	if(determinant){ // если не равен нулю то обратная матрица существует
		CFixedPointMAth::inverse(Matrix3x3,determinant,MatrixInv);
	}
	else{
		return;
	}
	
	//по формуле линейной интерполяции для матриц
	CFixedPointMAth::MulMatrix(MatrixRes,Matrix1x3,1,3,MatrixInv,3,3);
	CFixedPointMAth::MulMatrix(Matrix3x3,MatrixRes,1,3,Matrix3x1,3,1);

	Vertex.color = Matrix3x3[0][0]>>SHIFTKOEFF; // Возвращаем результат к исходному виду 
	
}


void CTriangle::BarycentricCoordInterpolate(_Vertex &Vertex)
{
	//интерполяция атрибутов вершин на основе барицентрических координат
	
	// Если текущая точка совпадает с одной из вершин треугольника то присвоить ей цвет вершины
	if(Vertex==mA){
		Vertex.color = mA.color;
		return;
	}
	if(Vertex==mB){
		Vertex.color = mB.color;
		return;
	}
	if(Vertex==mC){
		Vertex.color = mC.color;
		return;
	}

	int Numerator,Denominator;

	_Vertex CurrentPoint = Vertex;
	_Vertex tA,tB,tC;

	// Переходим к математике с фиксированой точкой
	CurrentPoint.x = TOFIXEDPOINT(CurrentPoint.x);
	CurrentPoint.y = TOFIXEDPOINT(CurrentPoint.y);

	tA.x = TOFIXEDPOINT(mA.x); 		 tA.color =  mA.color;
	tA.y = TOFIXEDPOINT(mA.y);		 tB.color =  mB.color;
	tB.x = TOFIXEDPOINT(mB.x);		 tC.color =  mC.color;
	tB.y = TOFIXEDPOINT(mB.y);		 tA.color = TOFIXEDPOINT( tA.color);
	tC.x = TOFIXEDPOINT(mC.x);		 tB.color = TOFIXEDPOINT( tB.color);
	tC.y = TOFIXEDPOINT(mC.y);		 tC.color = TOFIXEDPOINT( tC.color);

	Numerator	= CFixedPointMAth::MUL((tB.y - tC.y) ,(CurrentPoint.x	- tC.x)) + CFixedPointMAth::MUL((tC.x - tB.x), (CurrentPoint.y	- tC.y));
	Denominator = CFixedPointMAth::MUL((tB.y - tC.y) ,(tA.x				- tC.x)) + CFixedPointMAth::MUL((tC.x - tB.x), (tA.y			- tC.y));

	int l1 = CFixedPointMAth::DIV(Numerator,Denominator); 
    
	Numerator	= CFixedPointMAth::MUL((tC.y - tA.y) , (CurrentPoint.x - tC.x)) + CFixedPointMAth::MUL((tA.x - tC.x), (CurrentPoint.y	- tC.y));
	Denominator = CFixedPointMAth::MUL((tB.y - tC.y) , (tA.x		   - tC.x)) + CFixedPointMAth::MUL((tC.x - tB.x), (tA.y				- tC.y));
	 
    int l2 =  CFixedPointMAth::DIV(Numerator,Denominator); 
             
    int l3 = FIXPOINTKOEFF - (l1) - (l2);

	//Интерполяция
	if(l1 >= 0 && l1 <= FIXPOINTKOEFF && l2 >= 0 && l2 <= FIXPOINTKOEFF && l3 >= 0 && l3 <= FIXPOINTKOEFF){
		Vertex.color = (CFixedPointMAth::MUL(l1 , tA.color) + CFixedPointMAth::MUL(l2,tB.color) + CFixedPointMAth::MUL(l3,tC.color))>>SHIFTKOEFF;///FIXPOINTKOEFF ;
    }
	
	
}

void CTriangle::Draw()
{

	int Y = 0;

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
