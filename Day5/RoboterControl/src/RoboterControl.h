/*
 * RoboterControl.h
 *
 *  Created on: 07.10.2022
 *      Author: pi
 */

#ifndef ROBOTERCONTROL_H_
#define ROBOTERCONTROL_H_
#include "InterfaceSIM.h"
#include "Maneuver.h"
#include "PIDController.h"
#include "PosEstimation.h"
using namespace std;


class RoboterControl{

private:
	InterfaceSIM interface;
	Maneuver maneuver;
	PosEstimation posEstimation;
	PIDController motorR;
	PIDController motorL;
	bool bIsActive;
	static RoboterControl* transferPointer;
	double* actual_speed;
public:
	RoboterControl();
	static void transferFunction();
	bool isActive();
	void Step();
	void Communicate();

};




#endif /* ROBOTERCONTROL_H_ */
