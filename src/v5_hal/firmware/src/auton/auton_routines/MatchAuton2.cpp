#include "auton/auton_routines/MatchAuton2.h"

MatchAuton2::MatchAuton2(IDriveNode* drive_node, OdometryNode* odom_node, 
    IClawNode* front_claw_node, LiftNode* liftNode, BackClawNode* backClawNode,
    IRollerIntakeNode* intakeNode, IRollerIntakeNode* conveyorNode, IRollerIntakeNode* flapConveyorNode) : 
        Auton("Test Turn Node"), 
        m_drive_node(drive_node),
        m_odom_node(odom_node),
        m_front_claw_node(front_claw_node),
        m_liftNode(liftNode),
        m_backClawNode(backClawNode),
        m_intakeNode(intakeNode),
        m_conveyorNode(conveyorNode),
        m_flapConveyorNode(flapConveyorNode) {
    
}

void MatchAuton2::AddNodes() {
    // Set the starting position, as measured on the field
    Pose startingPose(Vector2d(-46, 11.375), Rotation2Dd(toRadians(92)));
    m_odom_node->setCurrentPose(startingPose);

    AutonNode* deploy = new AutonNode(0.1, new DeployAction());
    Auton::AddFirstNode(deploy);

    AutonNode* forward = new AutonNode(2, new DriveStraightAction(m_drive_node, m_odom_node, DRIVE_PARAMS, 35., 70., 80.));
    deploy->AddNext(forward);

    AutonNode* lowerLift = new AutonNode(2, new SetLiftStateAction(m_liftNode, LiftNode::LiftState::DOWN));
    deploy->AddNext(lowerLift);

    AutonNode* clawCloseDelay = new AutonNode(1.2, new WaitAction(1.2));
    deploy->AddNext(clawCloseDelay);
    
    AutonNode* clawClose = new AutonNode(0.5, new UseClawAction(m_front_claw_node, true));
    clawCloseDelay->AddNext(clawClose);

    Path firstBacking = PathManager::GetInstance()->GetPath("FirstBacking");
    AutonNode* firstBackingNode = new AutonNode(4, new FollowPathAction(m_drive_node, m_odom_node, new TankPathPursuit(firstBacking), firstBacking, false));
    clawClose->AddNext(firstBackingNode);
    
    AutonNode* clawOpen = new AutonNode(0.5, new UseClawAction(m_front_claw_node, false));
    firstBackingNode->AddNext(clawOpen);
    
    AutonNode* backClawOpen = new AutonNode(0.5, new SetBackClawStateAction(m_backClawNode, BackClawNode::BackClawState::PIVOT_DOWN_CLAW_OPEN));
    clawOpen->AddNext(backClawOpen);

    Path secondGrabYellow = PathManager::GetInstance()->GetPath("SecondGrabYellow");
    AutonNode* secondGrabYellowNode = new AutonNode(4, new FollowPathAction(m_drive_node, m_odom_node, new TankPathPursuit(secondGrabYellow), secondGrabYellow, false));
    firstBackingNode->AddNext(secondGrabYellowNode);
    
    AutonNode* clawClose2 = new AutonNode(0.5, new UseClawAction(m_front_claw_node, true));
    secondGrabYellowNode->AddNext(clawClose2);
    
    AutonNode* wait = new AutonNode(0.5, new WaitAction(0.5));
    secondGrabYellowNode->AddNext(wait);
    
    AutonNode* raiseLiftFullyUp = new AutonNode(0.5, new SetLiftStateAction(m_liftNode, LiftNode::LiftState::FULLY_UP));
    wait->AddNext(raiseLiftFullyUp);

    Path backingGrabBlue = PathManager::GetInstance()->GetPath("ThirdBackingGrabBlueGoal");
    AutonNode* backingGrabBlueNode = new AutonNode(10, new FollowPathAction(m_drive_node, m_odom_node, new TankPathPursuit(backingGrabBlue), backingGrabBlue, false));
    secondGrabYellowNode->AddNext(backingGrabBlueNode);
    
    AutonNode* backClawClosed = new AutonNode(0.5, new SetBackClawStateAction(m_backClawNode, BackClawNode::BackClawState::PIVOT_BACK));
    backingGrabBlueNode->AddNext(backClawClosed);
    
    AutonNode* clawOpen2 = new AutonNode(0.5, new UseClawAction(m_front_claw_node, false));
    backClawClosed->AddNext(clawOpen2);

    // Path turnRings = PathManager::GetInstance()->GetPath("FourthTurnRings");
    // AutonNode* turnRingsNode = new AutonNode(10, new FollowPathAction(m_drive_node, m_odom_node, new TankPathPursuit(turnRings), turnRings, false));
    // backingGrabBlueNode->AddNext(turnRingsNode);
    
    // AutonNode* wait2 = new AutonNode(1.5, new WaitAction(1.5));
    // backClawClosed->AddNext(wait2);
    
    // AutonNode* startRingIntake = new AutonNode(0.5, new RollerIntakeAction(m_intakeNode));
    // wait2->AddNext(startRingIntake);
    
    // AutonNode* startConveyor = new AutonNode(0.5, new RollerIntakeAction(m_conveyorNode));
    // wait2->AddNext(startConveyor);
    
    // AutonNode* startFlatConveyor = new AutonNode(0.5, new RollerIntakeAction(m_flapConveyorNode));
    // wait2->AddNext(startFlatConveyor);
}