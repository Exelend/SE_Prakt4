#ifndef HEIGHTLOGIC_H
#define	HEIGHTLOGIC_H
#include "FestoProcessAccess.h"
#include "plugin.h"

enum fsm_HeighLogic_states { BandHoehe, H1, H2, H3, H4, FalschesBauteil, RichtigesBauteil };

class HeightLogic {
private:
    FestoProcessAccess *process;
public:
    HeightLogic(FestoProcessAccess *process);
    ~HeightLogic();
    void evalCycle();
    bool result();
private:
    void stateChecker();
    void getNewHardwarestatus();
    void worker();
    fsm_HeighLogic_states currentState;

    unsigned short currentHeight;
    bool istRichtigsBauteil;
};

#endif	/* HEIGHTLOGIC_H */
