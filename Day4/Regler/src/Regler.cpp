//============================================================================
// Name        : Regler.cpp
// Author      : Qiyang
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
#include "PIDController.h"
#include <fstream>
#include <string>

void read_file(string Dateiname)
{
ifstream PIDInp;
string line;
double SollW[100];
double IstW[100];
PIDInp.open(Dateiname,ios::in);
PIDController obj(1000,10,10,0.5);
if (PIDInp.is_open())
	{
	int i = 0;
	while (!PIDInp.eof())
	{
		getline(PIDInp,line);
		PIDInp>>SollW[i]>>IstW[i];
		double W = SollW[i];
		double Y = IstW[i];
		obj.CauculateU(W,Y);
		cout << obj.getU() << endl;
		i++;
	}

	}
else
{cout<<"erorr! open fails!"<<endl;}

}
int main()
{
//PIDController obj(1000,10,10,0.5);
	read_file("PIDControllerInput.txt");
return 0;
}
