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
    //double time;
}

AutonAction::actionStatus PlatformBalance::Action() {
    //double time = m_timer.Get();
    //int distance = m_encoder_node->getValue();
    cout << "hello /n";
    if(m_timer.Get() > 20) {
        return END;
    }
    return CONTINUE;
}

void PlatformBalance::ActionEnd() {
    m_timer.Stop();
}