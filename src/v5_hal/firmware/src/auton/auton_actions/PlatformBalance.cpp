#include "auton/auton_actions/PlatformBalance.h"

PlatformBalance::PlatformBalance(IDriveNode* drive_node, ADIEncoderNode* encoder_node, InertialSensorNode* inertial_node) :
    m_drive_node(drive_node), 
    m_encoder_node(encoder_node),
    m_inertial_node(inertial_node)
    {
}

void PlatformBalance::ActionInit() {
    m_timer.Start();
    m_roll = m_inertial_node->getRoll();

}

AutonAction::actionStatus PlatformBalance::Action() {
    if (m_roll.angle() < 25) { //Phase 1: Driving onto the ramp
        m_drive_node->setDriveVelocity(100, 0); //should act as a checker for when the robot is fully on the ramp
    } else if(m_roll.angle() > 10) { //Phase 2: Driving until the ramp starts to tilt towards being balanced
        m_drive_node->setDriveVelocity(100, 0); //should drive until the ramp starts to balance
    } else {
        m_drive_node->setDriveVelocity(0, 0); //Phase 3: Balancing at a standstill
        return END;
    }
    return CONTINUE;
}

void PlatformBalance::ActionEnd() {
    m_timer.Stop();
}