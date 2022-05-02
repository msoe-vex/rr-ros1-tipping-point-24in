#include "auton/auton_routines/LeftAuton.h"

LeftAuton::LeftAuton(IDriveNode* drive_node, OdometryNode* odom_node, 
    IClawNode* front_claw_node, LiftNode* liftNode, HighRungLiftNode* highRingLiftNode, BackClawNode* backClawNode,
    IRollerIntakeNode* intakeNode, IRollerIntakeNode* conveyorNode, IRollerIntakeNode* flapConveyorNode) : 
        Auton("Default Left Auton"), 
        m_drive_node(drive_node),
        m_odom_node(odom_node),
        m_front_claw_node(front_claw_node),
        m_liftNode(liftNode),
        m_highRungLiftNode(highRingLiftNode),
        m_backClawNode(backClawNode),
        m_intakeNode(intakeNode),
        m_conveyorNode(conveyorNode),
        m_flapConveyorNode(flapConveyorNode) {
    
}

void LeftAuton::AddNodes() {
    // Set the starting position, as measured on the field
    Pose startingPose(Vector2d(-46, 11.375), Rotation2Dd(toRadians(82)));
    m_odom_node->setCurrentPose(startingPose);

    AutonNode* deploy = new AutonNode(0.1, new DeployAction());
    Auton::AddFirstNode(deploy);

    AutonNode* forward = new AutonNode(2, new DriveStraightAction(m_drive_node, m_odom_node, DRIVE_PARAMS, 35., 70., 80.));
    deploy->AddNext(forward);

    AutonNode* lowerLift = new AutonNode(2, new SetLiftStateAction(m_liftNode, LiftNode::LiftState::DOWN));

    AutonNode* clawCloseDelay = new AutonNode(1.2, new WaitAction(1.2));

    deploy->AddNext(lowerLift);
    deploy->AddNext(clawCloseDelay);
    
    AutonNode* clawClose = new AutonNode(0.5, new UseClawAction(m_front_claw_node, true));
    
    clawCloseDelay->AddNext(clawClose);

    Path firstBackingPath = PathManager::GetInstance()->GetPath("First");
    AutonNode* firstBackingNode = new AutonNode(
        4, 
        new FollowPathAction(
            m_drive_node, 
            m_odom_node, 
            new TankPathPursuit(firstBackingPath), 
            firstBackingPath, 
            false
        )
    );

    clawClose->AddNext(firstBackingNode);
    
    AutonNode* clawOpen = new AutonNode(0.5, new UseClawAction(m_front_claw_node, false));
    firstBackingNode->AddNext(clawOpen);
    
    AutonNode* backClawOpen = new AutonNode(0.5, new SetBackClawStateAction(m_backClawNode, BackClawNode::BackClawState::PIVOT_DOWN_CLAW_OPEN));
    clawOpen->AddNext(backClawOpen);

    Path secondGrabYellow = PathManager::GetInstance()->GetPath("Second");
    AutonNode* secondGrabYellowNode = new AutonNode(4, new FollowPathAction(m_drive_node, m_odom_node, new TankPathPursuit(secondGrabYellow), secondGrabYellow, false));
    firstBackingNode->AddNext(secondGrabYellowNode);
    
    AutonNode* clawClose2 = new AutonNode(0.5, new UseClawAction(m_front_claw_node, true));
    secondGrabYellowNode->AddNext(clawClose2);
    
    AutonNode* wait = new AutonNode(0.5, new WaitAction(0.5));
    secondGrabYellowNode->AddNext(wait);
    
    AutonNode* raiseLiftFullyUp = new AutonNode(0.5, new SetLiftStateAction(m_liftNode, LiftNode::LiftState::FULLY_UP));
    wait->AddNext(raiseLiftFullyUp);

    AutonNode* rearLiftUp = new AutonNode(0.1, new SetHighRungLiftStateAction(m_highRungLiftNode, HighRungLiftNode::STRAIGHT_UP));
    raiseLiftFullyUp->AddNext(rearLiftUp);

    Path backingGrabBlue = PathManager::GetInstance()->GetPath("Third");
    AutonNode* backingGrabBlueNode = new AutonNode(10, new FollowPathAction(m_drive_node, m_odom_node, new TankPathPursuit(backingGrabBlue), backingGrabBlue, false));
    secondGrabYellowNode->AddNext(backingGrabBlueNode);
    
    AutonNode* backClawClosed = new AutonNode(0.5, new SetBackClawStateAction(m_backClawNode, BackClawNode::BackClawState::PIVOT_BACK));
    backingGrabBlueNode->AddNext(backClawClosed);
    
    AutonNode* clawOpen2 = new AutonNode(0.5, new UseClawAction(m_front_claw_node, false));

    backClawClosed->AddNext(clawOpen2);

    Path turnRings = PathManager::GetInstance()->GetPath("Fourth");
    AutonNode* turnRingsNode = new AutonNode(
        10, 
        new FollowPathAction(
            m_drive_node, 
            m_odom_node, 
            new TankPathPursuit(turnRings), 
            turnRings, 
            false
        )
    );
    
    backingGrabBlueNode->AddNext(turnRingsNode);
    
    AutonNode* wait2 = new AutonNode(1.5, new WaitAction(1.5));
    backClawClosed->AddNext(wait2);

    AutonNode* raiseLiftRingHeight = new AutonNode(0.1, new SetLiftStateAction(m_liftNode, LiftNode::LiftState::UP_FOR_RINGS));
    
    AutonNode* startRingIntake = new AutonNode(0.5, new RollerIntakeAction(m_intakeNode));

    AutonNode* startConveyor = new AutonNode(0.5, new RollerIntakeAction(m_conveyorNode));

    AutonNode* startFlatConveyor = new AutonNode(0.5, new RollerIntakeAction(m_flapConveyorNode));

    wait2->AddNext(raiseLiftRingHeight);
    wait2->AddNext(startRingIntake);    
    wait2->AddNext(startConveyor);
    wait2->AddNext(startFlatConveyor);

    Path fifthReverseForTallGoalPath = PathManager::GetInstance()->GetPath("Fifth");
    AutonNode* fifthReverseForTallGoal = new AutonNode(
        4, 
        new FollowPathAction(
            m_drive_node, 
            m_odom_node, 
            new TankPathPursuit(fifthReverseForTallGoalPath), 
            fifthReverseForTallGoalPath, 
            false
        )
    );

    turnRingsNode->AddNext(fifthReverseForTallGoal);

    AutonNode* lowerLiftForTallGoal = new AutonNode(2, new SetLiftStateAction(m_liftNode, LiftNode::LiftState::DOWN));

    AutonNode* clawOpenForTallGoal = new AutonNode(0.1, new UseClawAction(m_front_claw_node, false));

    AutonNode* waitForLift = new AutonNode(1., new WaitAction(1.));

    fifthReverseForTallGoal->AddNext(lowerLiftForTallGoal);
    fifthReverseForTallGoal->AddNext(clawOpenForTallGoal);
    fifthReverseForTallGoal->AddNext(waitForLift);

    Path sixthMoveToTallGoalPath = PathManager::GetInstance()->GetPath("Sixth");
    AutonNode* sixthMovetoTallGoal = new AutonNode(
        4, 
        new FollowPathAction(
            m_drive_node, 
            m_odom_node, 
            new TankPathPursuit(sixthMoveToTallGoalPath), 
            sixthMoveToTallGoalPath, 
            false
        )
    );

    waitForLift->AddNext(sixthMovetoTallGoal);

    AutonNode* clawCloseForTallGoal = new AutonNode(0.1, new UseClawAction(m_front_claw_node, true));

    sixthMovetoTallGoal->AddNext(clawCloseForTallGoal);

    AutonNode* waitForTallGoalClose = new AutonNode(0.5, new WaitAction(0.5));
    clawCloseForTallGoal->AddNext(waitForTallGoalClose);

    AutonNode* raiseLiftTallGoal = new AutonNode(2, new SetLiftStateAction(m_liftNode, LiftNode::LiftState::FULLY_UP));
    waitForTallGoalClose->AddNext(raiseLiftTallGoal);

    AutonNode* waitForTallGoalLiftUp = new AutonNode(0.5, new WaitAction(0.5));
    raiseLiftTallGoal->AddNext(waitForTallGoalLiftUp);

    Path seventhPickUpRingsPath = PathManager::GetInstance()->GetPath("Seventh");
    AutonNode* seventhPickUpRings = new AutonNode(
        10, 
        new FollowPathAction(
            m_drive_node, 
            m_odom_node, 
            new TankPathPursuit(seventhPickUpRingsPath), 
            seventhPickUpRingsPath, 
            false
        )
    );

    waitForTallGoalLiftUp->AddNext(seventhPickUpRings);
}