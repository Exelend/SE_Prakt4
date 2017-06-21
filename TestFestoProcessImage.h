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

    virtual void updateProcessImage(void);
    virtual void applyOutputToProcess(void);
    virtual unsigned char isBitSet(unsigned short bitMask);
    virtual unsigned char isBitPosEdge(unsigned short bitMask);
    virtual unsigned char isBitNegEdge(unsigned short bitMask);
    virtual void setBitInOutput(unsigned short bitMask);
    virtual void clearBitInOutput(unsigned short bitMask);
    virtual unsigned short hight();
    virtual void resetOutputs(void);

    void setFSM(FSM* fsm);
private:
    int      bausteinWerte[1200][3]; // [x][0] Zeit; [x][1] Lichtschranke; [x][2] Hoehenwert;
    int		 durchlauf;
    int		 anzahlBausteinWerte;
    FSM* 	 fsm;
    bool     falschesBauteilErkannt;
};


#endif /* TESTFESTOPROCESSIMAGE_H_ */
