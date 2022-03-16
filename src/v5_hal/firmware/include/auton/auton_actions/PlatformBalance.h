#pragma once

#include "lib-rr/auton/Auton.h"
#include "lib-rr/util/Timer.h"

class PlatformBalace : public AutonAction {
private:
    Timer m_timer;

public:
    PlatformBalace();

    void ActionInit();

    actionStatus Action();
    
    void ActionEnd();
};
