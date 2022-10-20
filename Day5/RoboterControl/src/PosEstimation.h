/*
 * PosEstimation.h
 *
 *  Created on: 06.10.2022
 *      Author: pi
 */

#ifndef POSESTIMATION_H_
#define POSESTIMATION_H_
#include <cmath>

class PosEstimation
{
private:
	double x[3];
	double dVelAverage;
public:
	PosEstimation();
	void Reset();
	void PredictPosition(double dSpeedR, double dSpeedL, double dTimestep);
	double* GetPosition();
//	void PosCauculate(double dVr, double dVl, double dTime);
//	double getX();
//	double getY();
//	double getWink();

};




#endif /* POSESTIMATION_H_ */
