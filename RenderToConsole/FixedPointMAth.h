#ifndef _FIXED_POINT_H_
#define _FIXED_POINT_H_

#define FIXPOINTKOEFF		1024
#define SHIFTKOEFF			10
#define TOFIXEDPOINT(N)		N<<SHIFTKOEFF//M*FIXPOINTKOEFF   


class CFixedPointMAth
{
public:
	CFixedPointMAth(void);
	~CFixedPointMAth(void);

static	int ADD(int N1,int N2);
static	int SUB(int N1,int N2);
static	int MUL(int N1,int N2);
static	int DIV(int N1,int N2);


static int det(int a[3][3]);
static void inverse(int a[3][3], int d,int OutM[3][3]);

static void MulMatrix(int OutMx[3][3],int Mx1[3][3],int RowsMx1,int ColMx1,int Mx2[3][3],int RowsMx2,int ColMx2);

private:
static int add(int a[3][3],int row, int col);

};



#endif