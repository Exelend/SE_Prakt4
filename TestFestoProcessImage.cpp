/*
 * TestFestoProcessSensors.cpp
 *
 *  Created on: 31.05.2017
 *      Author: MaWi
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <array>
#include "TestFestoProcessImage.h"
#include "iomasks.h"
#include "HeightLogic.h"


using namespace std;



TestFestoProcessImage :: TestFestoProcessImage(){
    falschesBauteilErkannt = false;
    fsm = 0;
    ifstream file;
    char     filename[128];
    durchlauf = 0;
    anzahlBausteinWerte = 0;
    heightLogic = 0;
    endeZaehler = 0;

    // Dateinamen einlesen
    cout << "Dateinamen eingeben: ";
    cin.getline(filename, 127);

    // Datei oeffnen
    file.open(filename, ios::in);

    if (file.good()){
        // Wenn die Datei geoeffnet werden kann...

        // An den Anfang der Datei springen
        file.seekg(0L, ios::beg);
        int i = 0; // Datensatznumer
        while (!file.eof()){
            char charArray[30];
            std::fill(std::begin(charArray), std::end(charArray),0);
            char* pCharArray = charArray;
            // Die Datei zeilenweise auslesen
            file.getline(pCharArray, 30);

            // Chars in intArray ablegen
            int j = 0;
            for(int k = 0; k < 3; k++){
                    
                //char subCharArray[10];
                char subCharArray[30];
                for (int z = 0; z < 30; z++){
                    subCharArray[z] = '\0';
                }
                //std::fill(std::begin(subCharArray), std::end(subCharArray),0);
                int indexAlt = j;
                while(charArray[j] != ';' && charArray[j] != '\n'  && j <30){
                        subCharArray[j-indexAlt] = charArray[j];

                        j++;
                }
                bausteinWerte[i][k] = atoi(subCharArray);
                j++;
                j++;
                
            }
            cout << pCharArray << "\n";
            i++;
            anzahlBausteinWerte++;
        }
        
        cout << "auslesen fertig \n";
        for (int l= 0 ; l<anzahlBausteinWerte; l++) {
            cout << bausteinWerte[l][0] <<";"<< bausteinWerte[l][1] <<";"<< bausteinWerte[l][2] << "\n";
        }
    }else{
            // Wenn die Datei nicht geoeffnet werden konnte,
            cout << "Datei nicht gefunden.\n";
    }
    int kdk = 7;
}

TestFestoProcessImage::~TestFestoProcessImage(){
    delete fsm;
    delete heightLogic;    
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
	if(endeZaehler >=1){
            while(1);
        }
        if(fsm->currentState == StartReached){
            cout << "Falsches Bauteil!\n";
            endeZaehler++;
	} else if(fsm->currentState == EndReached){
            cout << "Bauteil OK!\n";
            endeZaehler++;
        }
        
}

void TestFestoProcessImage:: applyOutputToProcess(void){

}

unsigned char TestFestoProcessImage:: isBitSet(unsigned short bitMask){
	if(fsm->currentState == Ready && bitMask == ITEM_DETECTED ){
		return 0; // Active LOW!!!Bauteil am Anfang erkant
	} else if(bitMask == ITEM_DETECTED && fsm->currentState == ReverseTransport) {
		return 0; // Active Low! Bauteil-ruecktransport -> StartReached
	} else if(bitMask == ITEM_DETECTED && fsm->currentState == StartReached){
		return 1; // Active Low!! Bauteil zurueck am Start -> Ready                                                                       
	} else if((bitMask == ITEM_AT_JUNCTION) && (fsm->currentState == Transport) && (heightLogic->getState() == RichtigesBauteil)){
		return 0; //Active LOW!!!!! Bauteil okay -> zum Metalldetektor
	} else if( bitMask == ITEM_IS_METTAL){
		return 0; // Bauteil am Metalldetektor -> kein Metall
	} else if( bitMask == ITEM_AT_END && fsm->currentState == NonMetalic){
		return 0; // Active Low -> Bauteil zum Ende
	} else if( bitMask == ITEM_AT_END && fsm->currentState == EndReached){
		return 1; // Active Low -> Bauteil Am Ende->Ready
	} else if((bitMask == JUNCTION_IS_OPEN) || (bitMask == BUTTON_START_PRESSED) || (bitMask == BUTTON_RESET_PRESSED)){
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
            return 1; // StartButton gedrï¿½ckt
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
        this->heightLogic = dynamic_cast<HeightLogic*>(fsm->plugin);
}




