#include "auton/auton_routines/BasicAuton.h"

BasicAuton::BasicAuton(IDriveNode* drive_node, ADIEncoderNode* encoder_node, InertialSensorNode* inertial_node) : 
        Auton("Test Turn Node"), 
        m_drive_node(drive_node),
        m_encoder_node(encoder_node),
        m_inertial_node(inertial_node) {
    
}

void BasicAuton::AddNodes() {
    //AutonNode* forward_node = new AutonNode(10, new DriveStraightAction(m_drive_node, 60, 50, 10));
    //Auton::AddFirstNode(forward_node);

    AutonNode* platformBalance_node = new AutonNode(10, new PlatformBalance(m_drive_node, m_encoder_node, m_inertial_node));
}