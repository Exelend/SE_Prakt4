/*
 * TestFestoProcessImage.h
 *
 *  Created on: 31.05.2017
 *      Author: MaWi
 */

#ifndef TESTFESTOPROCESSIMAGE_H_
#define TESTFESTOPROCESSIMAGE_H_

#include "processimage.h"
#include "fsm.h"

class TestFestoProcessImage : public FestoProcessImage{

public:
	TestFestoProcessImage(void);
	virtual ~TestFestoProcessImage(void);

	void updateProcessImage(void);
	void applyOutputToProcess(void);
	unsigned char isBitSet(unsigned short bitMask);
	unsigned char isBitPosEdge(unsigned short bitMask);
	unsigned char isBitNegEdge(unsigned short bitMask);
	void setBitInOutput(unsigned short bitMask);
	void clearBitInOutput(unsigned short bitMask);
	unsigned short hight();
	void resetOutputs(void);

	void setFSM(FSM* fsm);
private:
	int      bausteinWerte[1200][3]; // [x][0] Zeit; [x][1] Lichtschranke; [x][2] Hoehenwert;
	int		 durchlauf;
	int		 anzahlBausteinWerte;
	FSM* 	 fsm;
};


#endif /* TESTFESTOPROCESSIMAGE_H_ */
