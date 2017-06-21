/** 
 * File:   factory.cpp
 *
 * Service class setting up all objects of the system.
 * 
 * \author  Prof. Dr. Thomas Lehmann
 * \version 1
 * \date    2013-11-10
 */

#include "factory.h"
#include "FestoProcessAccess.h"
#include "minilab1008processimage.h"
#include "plugin.h"
#include "HeightLogic.h"
#include "TestFestoProcessImage.h"

FSM* FSMFactory::createFSM(){
       // Create Objects
#ifdef SIL
	TestFestoProcessImage* processImage = new TestFestoProcessImage();
	FestoProcessAccess* processAccess = new FestoProcessAccess(processImage);
	Plugin* plugin = new  HeightLogic(processAccess);
	FSM* fsm = new FSM(processAccess, plugin);
	processImage->setFSM(fsm);
	return fsm;

#endif // SIL

#ifndef SIL
    FestoProcessImage* processImage = new FestoMiniLab1008ProcessImage();
    FestoProcessAccess* processAccess = new FestoProcessAccess(processImage);
    Plugin* plugin = new  HeightLogic(processAccess);
    FSM* fsm = new FSM(processAccess, plugin);
    return fsm;
#endif // SIL
}
