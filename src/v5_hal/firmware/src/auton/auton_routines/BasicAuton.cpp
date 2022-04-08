#include "auton/auton_routines/BasicAuton.h"

BasicAuton::BasicAuton(IDriveNode* drive_node, ADIEncoderNode* y_odom_encoder, InertialSensorNode* inertial_sensor) : 
        Auton("Test Turn Node"), 
        m_drive_node(drive_node),
        m_y_odom_encoder(y_odom_encoder),
        m_inertial_sensor(inertial_sensor) {
    
}

void BasicAuton::AddNodes() {
    AutonNode* forward_node = new AutonNode(10, new DriveStraightAction(m_drive_node, 60, 50, 10));
    Auton::AddFirstNode(forward_node);

    //AutonNode* platformBalance_Node = new AutonNode(10, new PlatformBalance(m_drive_node, m_y_odom_encoder, m_inertial_node));
    //Auton::AddFirstNode(platformBalance_Node);
}