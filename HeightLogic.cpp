/*
 * HeightLogic.cpp
 *
 *  Created on: 30.05.2017
 *      Author: MaWi
 */

#include "HeightLogic.h"


HeightLogic::HeightLogic(FestoProcessAccess *process){
	this->process = process;
	currentState = BandHoehe;
	currentHeight = process->getHight();
	istRichtigsBauteil = true;
}

HeightLogic::~HeightLogic(){
	delete process;
}

void Plugin::evalCycle(){
	HeightLogic->stateChecker();
	HeightLogic->worker();
}

void HeightLogic::getNewHardwarestatus(){
	currentHeight = process->getHight();
}

bool Plugin::result(){
	return HeightLogic->istRichtigsBauteil;
}

void HeightLogic::stateChecker(){
	switch (currentState) {
		case BandHoehe:
			if(currentHeight >= bandhoehe[1]-tolleranz){
				currentState = BandHoehe;
			} else if(currentHeight <= hoehe1_3 [0]+tolleranz && currentHeight >= hoehe1_3 [1]-tolleranz){
				currentState = H1;
			} else {
				currentState = FalschesBauteil;
			}
			break;
		case H1:
			if(currentHeight <= hoehe1_3 [0]+tolleranz && currentHeight >= hoehe1_3 [1]-tolleranz){
				currentState = H1;
			} else if(currentHeight <= hoehe2 [0]+tolleranz && currentHeight >= hoehe2 [1]-tolleranz){
				currentState = H2;
			} else {
				currentState = FalschesBauteil;
			}
			break;
		case H2:
			if(currentHeight <= hoehe2 [0]+tolleranz && currentHeight >= hoehe2 [1]-tolleranz){
				currentState = H2;
			} else if(currentHeight <= hoehe1_3 [0]+tolleranz && currentHeight >= hoehe1_3 [1]-tolleranz){
				currentState = H3;
			} else {
				currentState = FalschesBauteil;
			}
			break;
		case H3:
			if(currentHeight <= hoehe1_3 [0]+tolleranz && currentHeight >= hoehe1_3 [1]-tolleranz){
				currentState = H3;
			} else if(currentHeight <= hoehe4 [0]+tolleranz && currentHeight >= hoehe4 [1]-tolleranz){
				currentState = H4;
			} else {
				currentState = FalschesBauteil;
			}
			break;
		case H4:
			if(currentHeight <= hoehe4 [0]+tolleranz && currentHeight >= hoehe4 [1]-tolleranz){
				currentState = H4;
			} else if(currentHeight >= bandhoehe[1]-tolleranz){
				currentState = RichtigesBauteil;
			} else {
				currentState = FalschesBauteil;
			}
			break;
		case RichtigesBauteil:
			if(currentHeight >= bandhoehe[1]-tolleranz){
				currentState = BandHoehe;
			}
			break;
		case FalschesBauteil:
			if(process->isItemAtBeginning()){
				currentState = BandHoehe;
			}
			break;
	}
}

void HeightLogic::worker(){
	switch (currentState) {
		case BandHoehe:
			istRichtigsBauteil = true;
			break;
		case H1:
			istRichtigsBauteil = true;
			break;
		case H2:
			istRichtigsBauteil = true;
			break;
		case H3:
			istRichtigsBauteil = true;
			break;
		case H4:
			istRichtigsBauteil = true;
			break;
		case RichtigesBauteil:
			istRichtigsBauteil = true;
			break;
		case FalschesBauteil:
			istRichtigsBauteil = false;
			break;
	}
}
