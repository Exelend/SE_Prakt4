#ifndef HEIGHTLOGIC_H
#define	HEIGHTLOGIC_H
#include "FestoProcessAccess.h"
#include "plugin.h"

enum fsm_HeighLogic_states { BandHoehe, H1, H2, H3, H4, FalschesBauteil, RichtigesBauteil };

class HeightLogic : public Plugin {
private:
    FestoProcessAccess *process;
public:
    HeightLogic(FestoProcessAccess *process);
    ~HeightLogic(void);
    void evalCycle(void);
    bool result(void);
private:
    void stateChecker(void);
    void getNewHardwarestatus(void);
    void worker(void);
    fsm_HeighLogic_states currentState;
    unsigned short currentHeight;
    bool istRichtigsBauteil;
};

#endif	/* HEIGHTLOGIC_H */
