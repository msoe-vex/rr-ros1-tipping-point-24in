#include "auton/auton_actions/PlatformBalance.h"

PlatformBalance::PlatformBalance(IDriveNode* drive_node, ADIEncoderNode* encoder_node, InertialSensorNode* inertial_node) {

}

void PlatformBalance::ActionInit() {
    m_timer.Start();
}

AutonAction::actionStatus PlatformBalance::Action() {
    
}

void PlatformBalance::ActionEnd() {
    m_timer.Stop();
}