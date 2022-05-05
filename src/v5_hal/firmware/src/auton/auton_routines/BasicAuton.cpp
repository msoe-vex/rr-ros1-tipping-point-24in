#include "auton/auton_routines/BasicAuton.h"

BasicAuton::BasicAuton(IDriveNode* drive_node, OdometryNode* odom_node, HighRungLiftNode* high_rung_lift_node,
            GoalSpinnerNode* goalSpinnerNode, LiftNode* liftNode) : 
        Auton("Test Spinner"), 
        m_drive_node(drive_node),
        m_odom_node(odom_node),
        m_high_rung_lift_node(high_rung_lift_node),
        m_goalSpinnerNode(goalSpinnerNode),
        m_liftNode(liftNode) {
    
}

void BasicAuton::AddNodes() {
    AutonNode* deploy = new AutonNode(0.1, new DeployAction());
    Auton::AddFirstNode(deploy);

    AutonNode* HighRungLiftStraightUp = new AutonNode(0.1, new SetHighRungLiftStateAction(m_high_rung_lift_node, HighRungLiftNode::STRAIGHT_UP));
    
    deploy->AddNext(HighRungLiftStraightUp);

    AutonNode* LiftUpForRings = new AutonNode(0.1, new SetLiftStateAction(m_liftNode, LiftNode::UP_FOR_RINGS));
    
    deploy->AddNext(LiftUpForRings);

    AutonNode* SpinToPosition = new AutonNode(5, new MoveSpinnerToPositionAction(m_goalSpinnerNode, m_goalSpinnerNode->getPosition() + 3200, 0));

    HighRungLiftStraightUp->AddNext(SpinToPosition);

    AutonNode* wait = new AutonNode(2.0, new WaitAction(2.0));

    SpinToPosition->AddNext(wait);

    AutonNode* HighRungLiftScoring = new AutonNode(0.1, new SetHighRungLiftStateAction(m_high_rung_lift_node, HighRungLiftNode::SCORING));
    
    wait->AddNext(HighRungLiftScoring);

    // AutonNode* forward_node = new AutonNode(10, new SetHighRungLiftStateAction(m_high_rung_lift_node, HighRungLiftNode::HighRungLiftState::SCORING));
    // Auton::AddFirstNode(forward_node);

    //AutonNode* platformBalance_Node = new AutonNode(10, new PlatformBalance(m_drive_node, m_y_odom_encoder, m_inertial_node));
    //Auton::AddFirstNode(platformBalance_Node);
}