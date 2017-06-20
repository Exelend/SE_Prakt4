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

int      bausteinWerte[1200][3]; // [x][0] Zeit; [x][1] Lichtschranke; [x][2] Hoehenwert;
int		 durchlauf;
int		 anzahlBausteinWerte;

TestFestoProcessImage::TestFestoProcessImage(){
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
	return 0;
}

unsigned char TestFestoProcessImage:: isBitPosEdge(unsigned short bitMask){
	return 0;

}

unsigned char TestFestoProcessImage:: isBitNegEdge(unsigned short bitMask){
	if(durchlauf == 1){
		return BUTTON_START_PRESSED;
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




