/*
 * HeightLogic.cpp
 *
 *  Created on: 30.05.2017
 *      Author: MaWi
 */

#include "HeightLogic.h"


HightLogic::HightLogic(FestoProcessAccess *process){
	this->process = process;
	currentState = BandHoehe;
}

HightLogic::~HightLogic(){
	delete process;
}

void HightLogic::evalCycle(){
	this->stateChecker();
	this->worker();
}

void HightLogic::stateChecker(){
	switch (currentState) {
		case BandHoehe:
			if(process->getHight())
			break;
		case Standby:
}

void HightLogic::worker(){

}


