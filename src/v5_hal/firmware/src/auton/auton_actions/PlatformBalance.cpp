#include "auton/auton_actions/PlatformBalance.h"

PlatformBalance::PlatformBalance(IDriveNode* drive_node, ADIEncoderNode* encoder_node, InertialSensorNode* inertial_node) :
    m_drive_node(drive_node), 
    m_encoder_node(encoder_node),
    m_inertial_node(inertial_node) {
}

void PlatformBalance::ActionInit() {
    m_timer.Start();
    m_roll_offset = m_inertial_node->getRoll();
    m_start_value = m_encoder_node->getValue();
}

AutonAction::actionStatus PlatformBalance::Action() {
    double time = m_timer.Get();
    int distance = m_encoder_node->getValue();
    cout << distance << endl;

    return CONTINUE;
}

void PlatformBalance::ActionEnd() {
    m_timer.Stop();
}