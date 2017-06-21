/** 
 * File:   fsm.cpp
 *
 * Class contains the controlling FSM for sorting out metal contaminated parts.
 * 
 * \author  Prof. Dr. Thomas Lehmann
 * \version 1
 * \date    2013-11-01
 */

#include "fsm.h"
#include <iostream>


using namespace std;

FSM::FSM(FestoProcessAccess *process, Plugin* plugin) {
    this->process = process;
    currentState = Start;
    this->plugin = plugin;
}

FSM::~FSM() {
    delete plugin;
    delete process;
}

void FSM::eval() {
	//nur für SIL


    process->updateInputs();
    if (plugin != NULL) {
        plugin->evalCycle();
    }
    evalEvents();
    evalState();
    process->applyOutput();
}

void FSM::evalEvents() {
    switch (currentState) {
        case Start: // 1
            currentState = Standby;
            break;
        case Standby: // 2
            if (process->isButtonStartNegativeEdge()) {
                currentState = Ready;
            }
            cout << "Standby\n";
            break;
        case Ready: // 3
            if (process->isButtonStartNegativeEdge()) {
                currentState = Standby;
            }
            if (process->isItemAtBeginning()&& !process->isItemAtEnd()) {
                currentState = Transport;
            }
            if (process->isItemAtHightSensor() || process->isItemAtMetalDetector()) {
                currentState = Error;
            }
            cout << "Ready\n";
            break;
        case Transport:
            if (process->isItemAtMetalDetector()) {
                currentState = MetalDetection;
            }

// Neuer Code anfang
            if(plugin->result() == false){
            	currentState = ReverseTransport;
            }
// Neuer Code ende

            if (process->isItemAtEnd()) {
                currentState = Error;
            }
            cout << "Transport\n";
            break;
        case MetalDetection:
            if (process->isMetalDetected()) {
                currentState = Metalic;
            } else {
                currentState = NonMetalic;
            }
            cout << "Metalldetektion";
            break;
        case NonMetalic:
            if (process->isItemAtEnd()) {
                currentState = EndReached;
            }
            if (process->isItemAtBeginning() || process->isItemAtHightSensor()) {
                currentState = Error;
            }
            cout << "Kein Metall\n";
            break;
        case EndReached:
            if (process->isButtonStartNegativeEdge()) {
                currentState = Standby;
            }
            if (!(process->isItemAtEnd())) {
                currentState = Ready;
            }
            if (process->isItemAtMetalDetector() || process->isItemAtHightSensor()) {
                currentState = Error;
            }
            cout << "Am Ende\n";
            break;
        case Metalic:
            if (process->hasItemPassedSlide()) {
                currentState = SlideReached;
            }
            if (process->isItemAtBeginning() || process->isItemAtHightSensor()) {
                currentState = Error;
            }
            cout << "Metall erkannt\n";
            break;
        case SlideReached:
            if (process->isButtonStartNegativeEdge()) {
                currentState = Standby;
            }
            if (process->isItemAtBeginning()) {
                currentState = Transport;
            }
            if (process->isItemAtEnd() || process->isItemAtHightSensor()) {
                currentState = Error;
            }
            cout << "Rutsche erreicht\n";
            break;
        case Error:
            if (process->isButtonStartNegativeEdge()) {
                currentState = Standby;
            }
            cout << "Error\n";
            break;

// Neuer Code anfang
            /*
		case HeightDetection:
			if(plugin->result() == true){
				currentState = Transport;
			}	
			if(plugin->result() == false){ // TODO Bedingung aendern!!!!!!!! (result ist immer False, solange nicht ein Richtiges Teil erkannt wurde!)
				currentState = ReverseTransport;
			}	
			if(process->isItemAtBeginning() || process->isItemAtMetalDetector() || process->isItemAtEnd()){
				currentState = Error;
			}
			break;
			*/
		case ReverseTransport:
			if(process->isItemAtBeginning()){
				currentState = StartReached;
			}	
			if(process->isItemAtMetalDetector() || process->isItemAtEnd()){
				currentState = Error;
			}
			cout << "Rücktransport\n";
			break;
		case StartReached:
			if(!process->isItemAtBeginning()){
				currentState = Ready;
			}	
			if(process->isItemAtMetalDetector() || process->isItemAtHightSensor() || process->isItemAtEnd()){
				currentState = Error;
			}
			cout << "Bandanfang erreicht\n";
			break;
// Neuer Code ende
        default:
            currentState = Start;
    }
}

void FSM::evalState() {
    switch (currentState) {
        case Start:
        case Standby:
            process->driveStop();
            process->lightGreenOff();
            process->lightRedOff();
            process->lightYellowOff();
            process->turnLEDQ1Off();
            process->turnLEDQ2Off();
            process->turnLEDResetOff();
            process->turnLEDStartOn();
            break;
        case Ready:
            process->driveStop();
            process->lightGreenOn();
            process->lightRedOff();
            process->lightYellowOff();
            process->turnLEDStartOn();
            break;
        case Transport:
            process->driveRight();
            process->lightGreenOn();
            process->lightRedOff();
            process->lightYellowOff();
            process->turnLEDStartOff();
            break;
        case MetalDetection:
            process->driveStop();
            process->lightGreenOn();
            process->lightRedOff();
            process->lightYellowOff();
            break;
        case NonMetalic:
            process->driveRight();
            process->lightGreenOn();
            process->lightRedOff();
            process->lightYellowOff();
            process->turnLEDStartOff();
            process->openJunction();
            break;
        case EndReached:
            process->driveStop();
            process->lightRedOff();
            process->lightYellowOff();
            process->turnLEDStartOff();
            process->closeJunction();
            process->turnLEDStartOn();
            blinkGreen();
            break;
        case Metalic:
            process->driveRight();
            process->lightGreenOff();
            process->lightRedOff();
            process->lightYellowOn();
            break;
        case SlideReached:
            process->driveStop();
            process->lightGreenOn();
            process->lightRedOff();
            process->lightYellowOff();
            process->turnLEDStartOn();
            break;
        case Error:
            process->driveStop();
            process->lightGreenOff();
            process->lightYellowOff();
            process->turnLEDStartOn();
            process->closeJunction();
            blinkRed();
            break;
// Neuer Code Anfang
            /*
		case HeightDetection:
			process->driveRight();
            process->lightGreenOn();
            process->lightRedOff();
            process->lightYellowOff();
            process->turnLEDStartOff();
		break;
			*/
		case ReverseTransport:
			process->driveStop();
			process->lightGreenOff();
            process->lightYellowOff();
			blinkRed();
			process->driveLeft();
		break;
		case StartReached:
			process->driveStop();
			process->lightGreenOff();
            process->lightYellowOff();
		break;
// Neuer Code Ende
    }
}

void FSM::blinkRed() {
    if (process->timeCounter1s() & 0x01) {
        process->lightRedOn();
    } else {
        process->lightRedOff();
    }
}

void FSM::blinkGreen() {
    if (process->timeCounter1s() & 0x01) {
        process->lightGreenOn();
    } else {
        process->lightGreenOff();
    }
}
