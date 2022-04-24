#include "auton/auton_routines/BackClawTestAuton.h"

BackClawTestAuton::BackClawTestAuton(IDriveNode* drive_node, OdometryNode* odom_node, ADIEncoderNode* y_odom_encoder, InertialSensorNode* inertial_sensor,
            BackClawNode* backClaw) : 
        Auton("Test Turn Node"), 
        m_drive_node(drive_node),
        m_odom_node(odom_node),
        m_y_odom_encoder(y_odom_encoder),
        m_inertial_sensor(inertial_sensor),
        m_backClawNode(backClaw) {
    
}

void BackClawTestAuton::AddNodes() {
    AutonNode* backClawDownOpen = new AutonNode(10, new SetBackClawStateAction(m_backClawNode, BackClawNode::BackClawState::PIVOT_DOWN_CLAW_OPEN));
    Auton::AddFirstNode(backClawDownOpen);

    AutonNode* wait = new AutonNode(10, new WaitAction(2));
    backClawDownOpen->AddNext(wait);

    AutonNode* backClawDownClosed = new AutonNode(10, new SetBackClawStateAction(m_backClawNode, BackClawNode::BackClawState::PIVOT_DOWN_CLAW_CLOSED));
    wait->AddNext(backClawDownClosed);

    AutonNode* wait2 = new AutonNode(10, new WaitAction(2));
    backClawDownClosed->AddNext(wait2);

    AutonNode* backClawUp = new AutonNode(10, new SetBackClawStateAction(m_backClawNode, BackClawNode::BackClawState::PIVOT_BACK));
    wait2->AddNext(backClawUp);


    //AutonNode* platformBalance_Node = new AutonNode(10, new PlatformBalance(m_drive_node, m_y_odom_encoder, m_inertial_node));
    //Auton::AddFirstNode(platformBalance_Node);
}