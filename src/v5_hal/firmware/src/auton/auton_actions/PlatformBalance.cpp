#include "auton/auton_actions/PlatformBalance.h"

PlatformBalance::PlatformBalance(IDriveNode* drive_node, ADIEncoderNode* encoder_node, InertialSensorNode* inertial_node) :
    m_drive_node(drive_node), 
    m_encoder_node(encoder_node),
    m_inertial_node(inertial_node),
    m_climb_PID(0.00125, 0.003, 0) {
}

void PlatformBalance::ActionInit() {
    m_timer.Start();
    m_roll_offset = m_inertial_node->getRoll();
    m_finalEncoderValue = 1000;
}

AutonAction::actionStatus PlatformBalance::Action() {
    m_roll = m_inertial_node->getRoll();
    m_roll_true = m_roll * m_roll_offset.inverse();
    m_roll_true_angle = toDegrees(m_roll_true.angle())*-1;
    switch(m_phase) {
        case 1 :
            m_drive_node->setDriveVelocity(35, 0);
            if(m_roll_true_angle > 15) {
                m_phase = 2;
            }
            return CONTINUE;
        case 2 :
            m_EncoderValue = m_encoder_node->getValue();
            m_EncoderError = m_finalEncoderValue - m_EncoderValue;
            m_Velocity = m_climb_PID.calculate(m_EncoderError) * MAX_VELOCITY;
            if(m_Velocity < 0) {
                m_Velocity = 0;
            }
            m_drive_node->setDriveVelocity(m_Velocity, 0);
            if(m_roll_true_angle < 10) {
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