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
	cout << "Dateinamen eingeben: " << flush;
	cin.getline(filename, 127);

	// Datei öffnen
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
			cout << pCharArray << endl;
			i++;
			anzahlBausteinWerte++;
		}
	}else{
		// Wenn die Datei nicht geoeffnet werden konnte,
		cout << "Datei nicht gefunden." << endl;
	}
}

TestFestoProcessImage::~TestFestoProcessImage(){

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
}

void TestFestoProcessImage:: applyOutputToProcess(void){

}

unsigned char TestFestoProcessImage:: isBitSet(unsigned short bitMask){
	if(durchlauf == 3 && bitMask == ITEM_DETECTED ){
		return 0; // Active LOW!!!Bauteil am Anfang erkant
	} else if(durchlauf >= 800 && bitMask == ITEM_AT_JUNCTION && fsm->currentState == Transport && fsm->plugin->result()){
		return 1; //Active LOW!!!!! Bauteil okay -> zum Metalldetektor
	} else if( bitMask == ITEM_IS_METTAL){
		return 0; // Bauteil am Metalldetektor -> kein Metall
	} else if( bitMask == ITEM_AT_END && fsm->currentState == NonMetalic){
		return 0; // Active Low -> Bauteil zum Ende
	} else { // TODO  0 bzw. 1 zurückgeben!!!
		return 0;
	}
}

unsigned char TestFestoProcessImage:: isBitPosEdge(unsigned short bitMask){
	return 0;

}

unsigned char TestFestoProcessImage:: isBitNegEdge(unsigned short bitMask){
	if(durchlauf == 2 && bitMask == BUTTON_START_PRESSED){
		return 1; // StartButton gedrückt
	} else  if(durchlauf >= 1199 && bitMask == ITEM_AT_END){
		return 1; // Bauteil am Ende
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




