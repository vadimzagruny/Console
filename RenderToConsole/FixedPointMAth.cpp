#include "StdAfx.h"
#include "FixedPointMAth.h"


CFixedPointMAth::CFixedPointMAth(void)
{
}


CFixedPointMAth::~CFixedPointMAth(void)
{
}

//Сложение 
int CFixedPointMAth::ADD(int N1,int N2)
{
	int Result = 0;
	
	Result =  N1+N2;
	return Result ;	 
}
//вычитание
int CFixedPointMAth::SUB(int N1,int N2)
{
	int Result = 0;

	Result = N1-N1;
	return Result;
}
//умножение
int CFixedPointMAth::MUL(int N1,int N2)
{
	int Result = 0;
	if(N2 == 0) return 0;	

	Result = (N1*N2);

	if(Result/N2 != N1){
		// Overflow!
		int i1 = N1>>SHIFTKOEFF;
		int i2 = N2>>SHIFTKOEFF;
		int f1 = (N1&(FIXPOINTKOEFF-1));
		int f2 = (N1&(FIXPOINTKOEFF-1));
		return ((i1*i2)<<SHIFTKOEFF) + ((f1*f2)>>SHIFTKOEFF) + i1*f2 + i2*f1;
	}else{
		return Result >>SHIFTKOEFF;//Result = (N1*N2)/1024;;
	}

	//return Result >>SHIFTKOEFF;//Result = (N1*N2)/1024;;
	
}
//деление
int CFixedPointMAth::DIV(int N1,int N2)
{
	int Result = 0;
	if(N2 == 0) return 0;	

	if(N1>(1<<21)){
		// Overflow!
		int i = N1>>SHIFTKOEFF;
		int f = (N1&(FIXPOINTKOEFF-1));
		return ((((i<<SHIFTKOEFF)/N2)<<SHIFTKOEFF)+(f<<SHIFTKOEFF)/N2);
	}else{
		return Result = (N1<<SHIFTKOEFF)/N2;
	}

	//Result = (N1<<SHIFTKOEFF)/N2;//Result = (N1*1024)/N2;
	return (Result);
}
 
//алгебраическое допополнение к при расчете обратной матрицы
int CFixedPointMAth::add(int a[3][3],int row, int col)
{   
	int b[2][2];
    int i,j,bi,bj;
 
    for(i=0, bi=0;i<3;i++){   
		if(i!=row){   
			for(j=0, bj=0;j<3;j++){
                if(j!=col){   
					b[bi][bj]=a[i][j];
                    bj++;
                }
			}
            bi++;
        }
    }
    
    if((row+col)%2){
        return MUL(b[0][1],b[1][0]) - MUL(b[0][0],b[1][1]);
	}
    else{
        return MUL(b[0][0],b[1][1]) - MUL(b[0][1],b[1][0]);
	}
}
 
 
//определитель матрицы
int CFixedPointMAth::det(int a[3][3])
{   int i;
    int sum;
 
    for(i=0, sum=0;i<3;i++){
        sum += MUL(a[i][0],add(a,i,0));
	}
    return sum;
}
 
 
//обратная матрица
void CFixedPointMAth::inverse(int a[3][3], int d, int OutM[3][3])
{   int cur;
      
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            OutM[i][j] = DIV(add(a,i,j) , d);
		}
	}

    for(int i=0;i<3;i++){
        for(int j=i+1;j<3;j++){   cur = OutM[i][j];
			OutM[i][j] = OutM[j][i];
            OutM[j][i] = cur;
        }
	}
}
 //умножение матриц
 void CFixedPointMAth::MulMatrix(int OutMx[3][3],int Mx1[3][3],int RowsMx1,int ColMx1,int Mx2[3][3],int RowsMx2,int ColMx2)
 {
	OutMx[0][0] = 0; OutMx[0][1] = 0; OutMx[0][2] = 0;
	OutMx[1][0] = 0; OutMx[1][1] = 0; OutMx[1][2] = 0;
	OutMx[2][0] = 0; OutMx[2][1] = 0; OutMx[2][2] = 0;

	if(RowsMx2<ColMx1)return;//умножение невозможно

	for(int ColMat2 = 0;ColMat2<ColMx2;ColMat2++){
		for(int row = 0;row<RowsMx1;row++){
			for(int col = 0;col<ColMx1;col++){
				OutMx[row][ColMat2] += MUL(Mx1[row][col], Mx2[col][ColMat2]);
			}
		}
	}
 }