#include "auton/auton_routines/BasicAuton.h"

BasicAuton::BasicAuton(IDriveNode* drive_node, OdometryNode* odom_node, HighRungLiftNode* high_rung_lift_node) : 
        Auton("Test Turn Node"), 
        m_drive_node(drive_node),
        m_odom_node(odom_node),
        m_high_rung_lift_node(high_rung_lift_node) {
    
}

void BasicAuton::AddNodes() {
    AutonNode* forward_node = new AutonNode(10, new DriveStraightAction(m_drive_node, m_odom_node, DRIVE_CONFIG, 60, 50, 10));
    Auton::AddFirstNode(forward_node);

    //AutonNode* platformBalance_Node = new AutonNode(10, new PlatformBalance(m_drive_node, m_y_odom_encoder, m_inertial_node));
    //Auton::AddFirstNode(platformBalance_Node);
}