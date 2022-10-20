/*
 * PIDController.cpp
 *
 *  Created on: 06.10.2022
 *      Author: pi
 */
#include "PIDController.h"


PIDController::PIDController(double Kp, double Ki, double Kd, double Ta)
{
	dKp = Kp;
	dKi = Ki;
	dKd = Kd;
	dTa = Ta;
	dEsum = 0;
	deold = 0;
	dU = 0;
}

PIDController::~PIDController(){}

void PIDController::CauculateU(double dW, double dY)
{
	double e = dW - dY;
	dEsum = dEsum + e;
	dU = dKp*e + dKi*dTa*dEsum + dKd*(e - deold)/dTa ;
	deold = e;
}

double PIDController::getU()
{
return dU;
}


