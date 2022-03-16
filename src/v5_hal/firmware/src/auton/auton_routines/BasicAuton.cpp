#include "auton/auton_routines/BasicAuton.h"

BasicAuton::BasicAuton(IDriveNode* drive_node) : 
        Auton("Test Turn Node"), 
        m_drive_node(drive_node) {
    
}

void BasicAuton::AddNodes() {
    m_forward_node = new AutonNode(10, new DriveStraightAction(m_drive_node, 60, 50, 10));
    Auton::AddFirstNode(m_forward_node);
}