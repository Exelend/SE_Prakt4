/*
 * TestFestoProcessImage.h
 *
 *  Created on: 31.05.2017
 *      Author: MaWi
 */

#ifndef TESTFESTOPROCESSIMAGE_H_
#define TESTFESTOPROCESSIMAGE_H_

#include "processimage.h"

class TestFestoProcessImage : public FestoProcessImage{

private:

public:
	TestFestoProcessImage(void);
	virtual ~TestFestoProcessImage(void);

	virtual void updateProcessImage(void)=0;
	virtual void applyOutputToProcess(void)=0;
	virtual unsigned char isBitSet(unsigned short bitMask)=0;
	virtual unsigned char isBitPosEdge(unsigned short bitMask)=0;
	virtual unsigned char isBitNegEdge(unsigned short bitMask)=0;
	virtual void setBitInOutput(unsigned short bitMask)=0;
	virtual void clearBitInOutput(unsigned short bitMask)=0;
	virtual unsigned short hight()=0;
	virtual void resetOutputs(void)=0;

};


#endif /* TESTFESTOPROCESSIMAGE_H_ */
