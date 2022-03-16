#include "auton/auton_actions/PlatformBalance.h"

PlatformBalance::PlatformBalace() {

}

void PlatformBalance::ActionInit() {
    m_timer.Start();
}

AutonAction::actionStatus PlatformBalace::Action() {
    if (m_timer.Get() > 0.5) {
        return END;
    }

    return CONTINUE;
}

void PlatformBalace::ActionEnd() {
    m_timer.Stop();
}