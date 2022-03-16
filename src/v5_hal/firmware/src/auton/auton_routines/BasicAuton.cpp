#include "auton/auton_routines/BasicAuton.h"

BasicAuton::BasicAuton(IDriveNode* drive_node, IClawNode* claw_node, ILiftNode* lift_node) : 
        Auton("Test Turn Node"), 
        m_drive_node(drive_node),
        m_claw_node(claw_node) {
    
}

void BasicAuton::AddNodes() {
    m_forward_node = new AutonNode(10, new DriveStraightAction(m_drive_node, 60, 50, 10));
    Auton::AddFirstNode(m_forward_node);
    
    m_claw_open_node = new AutonNode(10, new UseClawAction(m_claw_node, true));
    m_forward_node->AddNext(m_claw_open_node);

    m_claw_close_node = new AutonNode(10, new UseClawAction(m_claw_node, false));
    m_claw_open_node->AddNext(m_claw_close_node);
    
    m_lift_up_node = new AutonNode(10, new MoveLiftToPositionAction(m_lift_up_node, 10, 2));
    //m_backward_node = new AutonNode(10, new DriveStraightAction(m_drive_node, 800, 10000, 10000));
    //m_claw_close_node->AddNext(m_claw_close_node);
}