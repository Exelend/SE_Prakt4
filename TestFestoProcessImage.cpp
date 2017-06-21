/*
 * TestFestoProcessSensors.cpp
 *
 *  Created on: 31.05.2017
 *      Author: MaWi
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "TestFestoProcessImage.h"
#include "iomasks.h"


using namespace std;



TestFestoProcessImage :: TestFestoProcessImage(){
	falschesBauteilErkannt = false;
	fsm = 0;
	ifstream file;
	char     filename[128];
	durchlauf = 0;
	anzahlBausteinWerte = 0;

	// Dateinamen einlesen
	cout << "Dateinamen eingeben: ";
	cin.getline(filename, 127);

	// Datei �ffnen
	file.open(filename, ios::in);

	if (file.good()){
		// Wenn die Datei geoeffnet werden kann...

		// An den Anfang der Datei springen
		file.seekg(0L, ios::beg);

		int i = 0; // Datensatznumer
		while (! file.eof()){
			char charArray[30];
			char* pCharArray = charArray;
			// Die Datei zeilenweise auslesen
			file.getline(pCharArray, 30);

			// Chars in intArray ablegen
			int indexAlt = 0;
			for(int k = 0; k < 2; k++){
				int j = 0;
				char subCharArray[10];
				while(charArray[j] != ';'){
					subCharArray[j] = charArray[j+indexAlt];
					j++;
				}
				bausteinWerte[i][k] = atoi(subCharArray);
				indexAlt = j+2;
			}
			cout << pCharArray << "\n";
			i++;
			anzahlBausteinWerte++;
		}
	}else{
		// Wenn die Datei nicht geoeffnet werden konnte,
		cout << "Datei nicht gefunden.\n";
	}
}

TestFestoProcessImage::~TestFestoProcessImage(){
	delete fsm;
}

unsigned short TestFestoProcessImage::hight(){
	durchlauf ++;
	if(durchlauf > anzahlBausteinWerte){
		throw std::out_of_range ("Test Durchgelaufen!");
	}
	return bausteinWerte[durchlauf][2];
}

void TestFestoProcessImage :: updateProcessImage(void){
	durchlauf++;
	if(durchlauf >= 900){
		exit(0);
	}
}

void TestFestoProcessImage:: applyOutputToProcess(void){

}

unsigned char TestFestoProcessImage:: isBitSet(unsigned short bitMask){
	if(durchlauf == 3 && bitMask == ITEM_DETECTED ){
		return 0; // Active LOW!!!Bauteil am Anfang erkant
	} else if(bitMask == ITEM_DETECTED && fsm->currentState == ReverseTransport) {
		return 0; // Active Low! Bauteil-r�cktransport -> StartReached
	} else if(bitMask == ITEM_DETECTED && fsm->currentState == StartReached){
		return 1; // Active Low!! Bauteil zur�ck am Start -> Ready
	} else if(durchlauf >= 800 && bitMask == ITEM_AT_JUNCTION && fsm->currentState == Transport && fsm->plugin->result()){
		return 1; //Active LOW!!!!! Bauteil okay -> zum Metalldetektor
	} else if( bitMask == ITEM_IS_METTAL){
		return 0; // Bauteil am Metalldetektor -> kein Metall
	} else if( bitMask == ITEM_AT_END && fsm->currentState == NonMetalic){
		return 0; // Active Low -> Bauteil zum Ende
	} else if( bitMask == ITEM_AT_END && fsm->currentState == EndReached){
		return 1; // Active Low -> Bauteil Am Ende->Ready
	} else if( bitMask == (JUNCTION_IS_OPEN || BUTTON_START_PRESSED || BUTTON_RESET_PRESSED)){
		return 0; // ActiveHigh default
	} else {
		return 1; // ActiveLow default
	}
}

unsigned char TestFestoProcessImage:: isBitPosEdge(unsigned short bitMask){
	return 0;

}

unsigned char TestFestoProcessImage:: isBitNegEdge(unsigned short bitMask){
	if(fsm->currentState == Standby && bitMask == BUTTON_START_PRESSED){
		return 1; // StartButton gedr�ckt
	} else {
		return 0;
	}
}

void TestFestoProcessImage:: setBitInOutput(unsigned short bitMask){

}

void TestFestoProcessImage:: clearBitInOutput(unsigned short bitMask){

}

void TestFestoProcessImage:: resetOutputs(void){

}

void TestFestoProcessImage :: setFSM(FSM* fsm){
	this->fsm = fsm;
}




