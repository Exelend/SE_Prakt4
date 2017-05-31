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
    // {Minimum, Maximum, Mittelwert, Mitte_Min-Max, Tolleranz}
    unsigned short tolleranz = 20;
    unsigned short bandhoehe[] = {3776, 3769, 3773,  };
    unsigned short hoehe1_3 [] = {3457, 3358, 3405, 3408, 50 };
    unsigned short hoehe2   [] = {3727, 3689, 3710, };
    unsigned short hoehe4   [] = {3112, 3033, 3068, };
    unsigned short currentHeight;
    bool istRichtigsBauteil;
};

#endif	/* HEIGHTLOGIC_H */
