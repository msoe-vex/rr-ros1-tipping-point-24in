#include "auton/auton_actions/PlatformBalance.h"

PlatformBalance::PlatformBalance() {

}

void PlatformBalance::ActionInit() {
    m_timer.Start();
}

AutonAction::actionStatus PlatformBalance::Action() {
    if (m_timer.Get() > 0.5) {
        return END;
    }

    return CONTINUE;
}

void PlatformBalance::ActionEnd() {
    m_timer.Stop();
}