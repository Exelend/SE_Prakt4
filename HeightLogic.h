#ifndef HEIGHTLOGIC_H
#define	HEIGHTLOGIC_H
#include "FestoProcessAccess.h"
#include "plugin.h"

enum fsm_HeighLogic_states { BandHoehe, H1, H2, H3, FalschesBauteil };

class HightLogic {
private:
    FestoProcessAccess *process;
public:
    HightLogic(FestoProcessAccess *process);
    ~HightLogic();
    void evalCycle();
    bool result();
private:
    void stateChecker();
    void worker();
    fsm_HeighLogic_states currentState;
    // {Minimum, Maximum, Mittelwert, Mitte_Min-Max, Tolleranz}
    unsigned short tolleranz = 20;
    unsigned short bandhoehe[] = {3776, 3769, 3773,  };
    unsigned short hoehe1_3 [] = {3457, 3358, 3405, 3408, 50 };
    unsigned short hoehe2   [] = {3727, 3689, 3710, };
    unsigned short hoehe4   [] = {3112, 3033, 3068, };
};

#endif	/* HEIGHTLOGIC_H */
