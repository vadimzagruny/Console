#include "StdAfx.h"



int main()
{

	CGraphicApplication *pApp = new CGraphicApplication;

	system("COLOR 0A");

	int Size = 0;
	int ColA = 0;
	int ColB = 0;
	int ColC = 0;

	cout << "Hy!"<<endl;
	cout << "Enter Size for Triangle from 0 to 64"<<endl;	
	cin  >>  Size;
	cout << "Enter Color of Point A from 0 to 9"<<endl;
	cin  >>  ColA;
	cout << "Enter Color of Point B from 0 to 9"<<endl;
	cin  >>  ColB;
	cout << "Enter Color of Point C from 0 to 9"<<endl;
	cin  >>  ColC;
	cout << endl;


	//Добавим треугольник
	pApp->AddTriangle(Size,ColA,ColB,ColC);

	//Вывод треугольника
	pApp->Draw();

	delete pApp;

	getchar();
	getchar();

	return 0;
}