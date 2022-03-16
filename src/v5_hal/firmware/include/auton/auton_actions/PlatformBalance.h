#pragma once

#include "lib-rr/auton/Auton.h"
#include "lib-rr/util/Timer.h"

class PlatformBalance : public AutonAction {
private:
    Timer m_timer;

public:
    PlatformBalance();

    void ActionInit();

    actionStatus Action();
    
    void ActionEnd();
};
