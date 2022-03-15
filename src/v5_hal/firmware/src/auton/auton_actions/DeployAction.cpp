#include "auton/auton_actions/DeployAction.h"

DeployAction::DeployAction() {

}

void DeployAction::ActionInit() {
    m_timer.Start();
}

AutonAction::actionStatus DeployAction::Action() {
    if (m_timer.Get() > 0.5) {
        return END;
    }

    return CONTINUE;
}

void DeployAction::ActionEnd() {
    m_timer.Stop();
}