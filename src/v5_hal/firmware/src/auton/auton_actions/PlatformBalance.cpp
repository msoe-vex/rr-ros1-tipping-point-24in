#include "auton/auton_actions/PlatformBalance.h"

PlatformBalance::PlatformBalance(IDriveNode* drive_node, ADIEncoderNode* encoder_node, InertialSensorNode* inertial_node) :
    m_drive_node(drive_node), 
    m_encoder_node(encoder_node),
    m_inertial_node(inertial_node)

    {
}

void PlatformBalance::ActionInit() {
    m_timer.Start();
    m_roll_offset = m_inertial_node->getRoll();

}

AutonAction::actionStatus PlatformBalance::Action() {
    m_roll = m_inertial_node->getRoll();
    m_roll_true = (m_roll* m_roll_offset).smallestAngle();
    switch(m_phase) {
        case 1 :
            m_drive_node->setDriveVelocity(10, 0);
            if(m_roll_true > 15) {
                m_phase = 2;
            }
            return CONTINUE;
        case 2 :
            m_drive_node->setDriveVelocity(10, 0);
            if(m_roll_true < 5) {
                m_phase = 3;
            }
            return CONTINUE;
        case 3 : 
            m_drive_node->setDriveVelocity(0, 0);
            return END;
    }
    return END;
}

void PlatformBalance::ActionEnd() {
    m_timer.Stop();
}