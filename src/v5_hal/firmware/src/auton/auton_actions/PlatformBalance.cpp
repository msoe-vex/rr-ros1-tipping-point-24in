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
    switch(m_phase) {
        case 1 :
            m_drive_node->setDriveVelocity(100, 0);
            if(m_roll.angle() > 25) {
                m_phase = 2;
            }
        case 2 :
            m_drive_node->setDriveVelocity(80, 0);
            if(m_roll.angle() < 10) {
                m_phase = 3;
            }
        case 3 : 
            m_drive_node->setDriveVelocity(0, 0);
            return END;
    }
}

void PlatformBalance::ActionEnd() {
    m_timer.Stop();
}