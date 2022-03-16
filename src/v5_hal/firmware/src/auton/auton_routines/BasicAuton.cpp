#include "auton/auton_routines/BasicAuton.h"

BasicAuton::BasicAuton(IDriveNode* drive_node) : 
        Auton("Test Turn Node"), 
        m_drive_node(drive_node) {
    
}

void BasicAuton::AddNodes() {
    m_forward_node = new AutonNode(10, new DriveStraightAction(m_drive_node, 30, 50, 10));
    Auton::AddFirstNode(m_forward_node);
    

    //m_claw_close_node = new AutonNode(10, new UseClawAction(m_claw_node, false));
    //Auton::AddFirstNode(m_claw_close_node);
    //m_forward_node->AddNext(m_claw_close_node);

    //m_backward_node = new AutonNode(10, new DriveStraightAction(m_drive_node, 800, 10000, 10000));
    //m_claw_close_node->AddNext(m_claw_close_node);
}