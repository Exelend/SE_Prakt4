/*
 * HeightLogic.cpp
 *
 *  Created on: 30.05.2017
 *      Author: MaWi
 */

#include "HeightLogic.h"
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

// {Minimum, Maximum, Mittelwert, Mitte_Min-Max, Tolleranz}
    unsigned short tolleranz = 20;
    unsigned short bandhoehe[] = {3776, 3769, 3773};
    unsigned short hoehe1_3[] = {3457, 3358, 3405, 3408, 50};
    unsigned short hoehe2[] = {3727, 3689, 3710};
    unsigned short hoehe4[] = {3112, 3033, 3068};

HeightLogic::HeightLogic(FestoProcessAccess *process){
    this->process = process;
    currentState = BandHoehe;
    currentHeight = process->getHight();
    istRichtigsBauteil = true;
}

HeightLogic::~HeightLogic(){
    delete process;
}

void HeightLogic::evalCycle(){
    getNewHardwarestatus();
    stateChecker();
    worker();
}

void HeightLogic::getNewHardwarestatus(){
    currentHeight = process->getHight();
}

bool HeightLogic::result(){
    return istRichtigsBauteil;
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
            if(currentHeight <= hoehe1_3 [0]+tolleranz && currentHeight >= hoehe1_3[1] - tolleranz){
                    currentState = H3;
            } else if(currentHeight <= hoehe4 [0]+tolleranz && currentHeight >= hoehe4[1] - tolleranz){
                    currentState = H4;
            } else {
                    currentState = FalschesBauteil;
            }
            break;
        case H4:
            if(currentHeight <= hoehe4[0] + tolleranz && currentHeight >= hoehe4[1] - tolleranz){
                    currentState = H4;
            } else if(currentHeight >= bandhoehe[1]-tolleranz){
                    currentState = RichtigesBauteil;
            } else {
                    currentState = FalschesBauteil;
            }
            break;
        case RichtigesBauteil:
            //cout << "Richtiges BT\n";
            if(currentHeight >= bandhoehe[1]-tolleranz && process->isItemAtMetalDetector()){
                    currentState = BandHoehe;
            }
            break;
        case FalschesBauteil:
            if(process->isItemAtBeginning()){
                    currentState = BandHoehe;
                    //cout << "Falsches BT\n";
            }
            
            ofstream fileO ("logfile.txt", std::ofstream::app);
            fileO << clock() << " Bauteil fehlerhaft\n";
            fileO.close();
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

fsm_HeighLogic_states HeightLogic::getState(){
    return currentState;
}