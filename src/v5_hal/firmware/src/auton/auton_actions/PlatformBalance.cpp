#include "auton/auton_actions/PlatformBalance.h"

PlatformBalance::PlatformBalance(IDriveNode* drive_node, ADIEncoderNode* encoder_node, InertialSensorNode* inertial_node) :
    m_drive_node(drive_node), 
    m_encoder_node(encoder_node),
    m_inertial_node(inertial_node) {
}

void PlatformBalance::ActionInit() {
    m_timer.Start();
    m_roll_offset = m_inertial_node->getRoll();
}

AutonAction::actionStatus PlatformBalance::Action() {
    m_roll = m_inertial_node->getRoll();
    //m_roll_true = (m_roll* m_roll_offset).smallestAngle();
    m_roll_true = m_roll * m_roll_offset.inverse();
    m_roll_true_angle = m_roll_true.angle();
    cout << "TR: " << toDegrees(m_roll_true_angle) << "\n";
    /*switch(m_phase) {
        case 1 :
            if ((int) m_timer.getTime() % 5 == 0){
                cout << "True Roll is: " << toDegrees(m_roll_true) << "\n" << "Hit case 1\n";
            }
            m_drive_node->setDriveVelocity(10, 0);
            if(m_roll_true > toRadians(15)) {
                m_phase = 2;
            }//else {
            //    return CONTINUE;
            //}
            return CONTINUE;
        case 2 :
            if ((int) m_timer.getTime() % 5 == 0){
                cout << "True Roll is: " << toDegrees(m_roll_true) << "\n" << "Hit case 2\n";
                
            }
            m_drive_node->setDriveVelocity(0, 0);
            if(m_roll_true < toRadians(10)) {
                m_phase = 3;
            } //else {
            //    return CONTINUE;
            //}
            return CONTINUE;
        case 3 : 
            if ((int) m_timer.getTime() % 5 == 0){
                cout << "True Roll is: " << toDegrees(m_roll_true) << "\n" << "Hit case 3\n";
            }
            m_drive_node->setDriveVelocity(0, 0);
            return END;
    }
    return END;*/
    return CONTINUE;
}

void PlatformBalance::ActionEnd() {
    m_timer.Stop();
}