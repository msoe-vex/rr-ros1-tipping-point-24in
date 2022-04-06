#include "auton/auton_routines/BasicAuton.h"

BasicAuton::BasicAuton(IDriveNode* drive_node, OdometryNode* odom_node) : 
        Auton("Test Turn Node"), 
        m_drive_node(drive_node),
        m_odom_node(odom_node) {
    
}

void BasicAuton::AddNodes() {
    //AutonNode* forward_node = new AutonNode(10, new DriveStraightAction(m_drive_node, 60, 50, 10));
    //Auton::AddFirstNode(forward_node);

    Auton::AddFirstNode(platformBalance_node);
}