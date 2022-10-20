//============================================================================
// Name        : RoboterControl.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
#include "ncurses.h"
#include "RoboterControl.h"
#include "PIDController.h"
#include "Maneuver.h"
#include "PosEstimation.h"

RoboterControl* RoboterControl::transferPointer;

RoboterControl::RoboterControl():motorR(500.0,100.0,0.0,0.04), motorL(500.0,100.0,0.0,0.04)
{
	interface.Initialize(0.04, RoboterControl::transferFunction);
	RoboterControl::transferPointer = this;
//	motorR = PIDController(500.0,100.0,0.0,0.04);
//	motorL = PIDController(500.0,100.0,0.0,0.04);
	bIsActive = false;
}

void RoboterControl::Communicate(){

    while(true){
    	string buf;
    	cout<<"do you want to start a test? y/n"<<endl;
    	cin>>buf;
    	if(buf=="n"){
    		bIsActive = false;
    		break;
    	}
    	string s_type, s_radius, s_volume;
    	double radius, volume;
    	cout<<"please enter type(0 or 8), radius and speed:"<<endl;
		cin>>s_type>>s_radius>>s_volume;
		radius = stod(s_radius);
		volume = stod(s_volume);

		if(s_type=="0") maneuver.CalcCircle(radius, volume, 0.04);
		else if(s_type=="8") maneuver.CalcEight(radius, volume, 0.04);

		posEstimation.Reset();

		initscr();
		nodelay(stdscr, true);
		noecho();

	    sigprocmask(SIG_UNBLOCK, &interface.mask, nullptr);

		int input;

		while(true){
			input = getch();
			if(input!=-1){
				clear();
				if(input=='s'){
					maneuver.Start();
				}
				else if(input=='b'){
					maneuver.Stop();
				}
				else if(input=='p'){
					maneuver.Proceed();
				}
				else if (input=='q'){
					maneuver.Stop();
					break;
				}

//				printw("desired speed: %f , %f\n", should_speed[1], should_speed[0]);
//				printw("actual speed: %f , %f\n", actual_speed[1], actual_speed[0]);
			}

		}
		endwin();
		while(true){
			if(*actual_speed==0.0&&*(actual_speed+1)==0.0){
				cout<<"robot is stopped"<<endl;
				break;
			}
		}

	    sigprocmask(SIG_BLOCK, &interface.mask, nullptr);

    }




}

void RoboterControl::Step(){
	actual_speed = interface.GetInput();
	double* should_speed;
	double* pos;
	int* signal_length = new int[2];

	if(!maneuver.isRunning()){
		signal_length[0] = 1500;
		signal_length[1] = 1500;
		interface.SetOutputs(signal_length);
		delete[] signal_length;
		return;
	}


	posEstimation.PredictPosition(*actual_speed, *(actual_speed+1),0.04);
	pos = posEstimation.GetPosition();
	maneuver.CalcManeuverSpeed(*pos, *(pos+1), *(pos+2));
	should_speed = maneuver.GetManeuverSpeed();

//	motorR.CalculateU(*should_speed,*actual_speed);
//	motorL.CalculateU(*(should_speed+1),*(actual_speed+1));
	motorR.CauculateU(*should_speed, *actual_speed);
	motorL.CauculateU(*(should_speed+1),*(actual_speed+1));

	signal_length[0] = 1500+motorR.getU();
	signal_length[1] = 1500+motorL.getU();

	signal_length[0] = min(max(1000,signal_length[0]),2000);
	signal_length[1] = min(max(1000,signal_length[1]),2000);

	interface.SetOutputs(signal_length);

	delete[] signal_length;
}

void RoboterControl::transferFunction(){
    transferPointer -> Step();
}



