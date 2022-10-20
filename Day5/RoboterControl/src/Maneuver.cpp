//============================================================================
// Name        : Maneuver.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
#include <cmath>
#include<fstream>
#include <string>
#include "Maneuver.h"

Maneuver::Maneuver()
{
dMaxSpeed = 0.5;
dPosDifference = 0.02;
bIsRunning = false;
}

void Maneuver::LogList(string Dateiname)
{
	ofstream file(Dateiname, ios::out|ios::trunc);
	for(auto it=Coordlist.begin(); it!=Coordlist.end(); it++){
		file<<it->dX<<'\t'<<it->dY<< endl;
	}
	file.close();
}

void Maneuver::CalcCircle(double dRadius, double dSpeed, double dTimestep)
{
	Coordlist.clear();
	int n = (int)((2*M_PI)/(dSpeed/dRadius*dTimestep));
	double x,y,temp;
	for(int counter=1; counter<n; counter++)
	{
		temp = counter * dSpeed * dTimestep / dRadius;
		x = dRadius * sin(temp);
		y = dRadius * (1 - cos(temp));
		Coordlist.push_back(Coord(x,y,dSpeed));
	}

	LogList("LogFileCircle.txt");
}

void Maneuver::CalcEight(double dRadius, double dSpeed, double dTimestep)
{
	Coordlist.clear();
	int n = (int)((2*M_PI)/(dSpeed/dRadius*dTimestep));
	double x,y,temp;

	for(int counter=1; counter<n; counter++)
	{
		temp = counter * dSpeed * dTimestep / dRadius;
		x = dRadius * sin(temp);
		y = dRadius * (1 - cos(temp));
		Coordlist.push_back(Coord(x,y,dSpeed));
	}

	for(int counter=1; counter<n; counter++)
	{
		temp = counter * dSpeed * dTimestep / dRadius;
		x = dRadius * sin(temp);
		y = -dRadius * (1 - cos(temp));
		Coordlist.push_back(Coord(x,y,dSpeed));
	}
	LogList("LogFileEight.txt");

}

bool Maneuver::isRunning()
{
return bIsRunning;
}

void Maneuver::Start()
{
iter = Coordlist.begin();
bIsRunning = true;
}

void Maneuver::Stop()
{
	bIsRunning = false;
}

void Maneuver::Proceed()
{
	bIsRunning = true;
}

void Maneuver::CalcManeuverSpeed(double dX, double dY, double dW)
{
	if(pow(iter->dX-dX, 2) + pow(iter->dY-dY, 2)<=0.0025)
	{
		iter++;
		return;
	}

	if(iter==Coordlist.end())
	{
		adWishSpeed[0] = 0.0;
		adWishSpeed[1] = 0.0;
		Stop();
		return;
	}

	double delta_phi = atan2(iter->dY-dY, iter->dX-dX) - dW;
	while(delta_phi>M_PI) delta_phi -= 2*M_PI;
	while(delta_phi<-M_PI) delta_phi += 2*M_PI;

	double dRot = 2*delta_phi;
	double dTra = iter->dV;

	if(dTra*dRot>0.0)
	{
		if(dTra+dRot>dMaxSpeed) dTra = dMaxSpeed-dRot;
		else if(dTra+dRot<-dMaxSpeed) dTra = -dMaxSpeed-dRot;
	}
	else if(dTra*dRot<0.0)
	{
		if(dTra-dRot>dMaxSpeed) dTra = dMaxSpeed+dRot;
		else if(dTra-dRot<-dMaxSpeed) dTra = -dMaxSpeed+dRot;
	}

	adWishSpeed[0] = dTra+dRot;
	adWishSpeed[1] = dTra-dRot;
}

double* Maneuver::GetManeuverSpeed()
{
return &adWishSpeed[0];
}





