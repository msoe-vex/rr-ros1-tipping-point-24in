#include "auton/auton_routines/ProgrammingSkillzAuton.h"

ProgrammingSkillzAuton::ProgrammingSkillzAuton(IDriveNode* driveNode, OdometryNode* odomNode, IRollerIntakeNode* intakeNode, 
        IRollerIntakeNode* conveyorNode, IRollerIntakeNode* flapConveyorNode, IClawNode* frontClawNode, 
        BackClawNode* backClaw, IClawNode* buddyClimb, LiftNode* liftNode, 
        HighRungLiftNode* highRungLiftNode, GoalSpinnerNode* goalSpinner) : 
        Auton("ProgSkills", "/usd/paths/path24inProgPt1v5.json"), 
        m_driveNode(driveNode),
        m_odomNode(odomNode),
        m_intakeNode(intakeNode),
        m_conveyorNode(conveyorNode),
        m_flapConveyorNode(flapConveyorNode),
        m_frontClawNode(frontClawNode),
        m_backClaw(backClaw),
        m_buddyClimb(buddyClimb),
        m_liftNode(liftNode),
        m_highRungLiftNode(highRungLiftNode),
        m_goalSpinner(goalSpinner) {
    
}

void ProgrammingSkillzAuton::AddNodes() {
    // Set the starting position, as measured on the field
    // Pose startingPose(Vector2d(38.4375, 13.625), Rotation2Dd(3.525));
    // m_odomNode->setCurrentPose(startingPose);
    // 1. Deploy
    AutonNode* deploy = new AutonNode(0.1, new DeployAction());
    Auton::AddFirstNode(deploy);

    // Start ring intake to pickup and rings we happen to encounter along the way
    AutonNode* startRingIntake = new AutonNode(0.1, new RollerIntakeAction(m_intakeNode));

    deploy->AddNext(startRingIntake);
    
    // 2a. Open Back Claw
    AutonNode* OpenBackClaw1 = new AutonNode(0.1, new SetBackClawStateAction(m_backClaw, BackClawNode::PIVOT_DOWN_CLAW_OPEN));
    
    deploy->AddNext(OpenBackClaw1);

    // Put the High Rung Lift straight up
    AutonNode* HighRungLiftStraightUp = new AutonNode(0.1, new SetHighRungLiftStateAction(m_highRungLiftNode, HighRungLiftNode::STRAIGHT_UP));
    
    deploy->AddNext(HighRungLiftStraightUp);

    // 2b. Path to First Goal
    Path StartToBlueGoal = PathManager::GetInstance()->GetPath("StartToBlueGoal");
    AutonNode* StartToBlueGoalNode = new AutonNode(10, new FollowPathAction(m_driveNode, m_odomNode, new TankPathPursuit(StartToBlueGoal), StartToBlueGoal, true));

    deploy->AddNext(StartToBlueGoalNode);

    // 4c. Open Front Claw
    AutonNode* OpenFrontClaw1 = new AutonNode(0.1, new UseClawAction(m_frontClawNode, false));

    StartToBlueGoalNode->AddNext(OpenFrontClaw1);
    
    // Lower lift
    AutonNode* LowerLift = new AutonNode(0.1, new SetLiftStateAction(m_liftNode, LiftNode::DOWN));
    
    OpenFrontClaw1->AddNext(LowerLift);

    // 3b. Close Back Claw= Grab First Goal
    AutonNode* CloseBackClaw1 = new AutonNode(0.1, new SetBackClawStateAction(m_backClaw, BackClawNode::PIVOT_BACK));

    StartToBlueGoalNode->AddNext(CloseBackClaw1);

    // Wait 2 seconds after picking up goal to start scoring rings
    AutonNode* waitToStartScoringRings = new AutonNode(2.0, new WaitAction(2.0));

    CloseBackClaw1->AddNext(waitToStartScoringRings);

    // Turn on conveyor
    AutonNode* startConveyor = new AutonNode(0.1, new RollerIntakeAction(m_conveyorNode));
    
    waitToStartScoringRings->AddNext(startConveyor);

    // Turn on flap conveyor
    AutonNode* startFlapConveyor = new AutonNode(0.1, new RollerIntakeAction(m_flapConveyorNode));
    
    waitToStartScoringRings->AddNext(startFlapConveyor);

    // Wait for robot to pick up alliance goal
    AutonNode* waitToPickup = new AutonNode(1.0, new WaitAction(1.0));

    CloseBackClaw1->AddNext(waitToPickup);

    // 4b. Path to Second Goal
    // Do this after waiting for the back claw
    Path BlueGoalToYellowGoal = PathManager::GetInstance()->GetPath("BlueGoalToYellowGoal");
    AutonNode* BlueGoalToYellowGoalNode = new AutonNode(10, new FollowPathAction(m_driveNode, m_odomNode, new TankPathPursuit(BlueGoalToYellowGoal), BlueGoalToYellowGoal, false));

    waitToPickup->AddNext(BlueGoalToYellowGoalNode);


    /**
     * This commented out section used to be actions for picking up rings before the yelow goal
     * It has since been taken out of this Auton
     * */
    // raise the goal above the rings
    // AutonNode* RaiseLift = new AutonNode(0.1, new SetLiftStateAction(m_liftNode, LiftNode::UP_FOR_RINGS));
    
    // StartToBlueGoalNode->AddNext(RaiseLift);

    //  Turn on Ring Intake
    // AutonNode* EnableRingIntake = new AutonNode(0.1, new RollerIntakeAction(m_intakeNode));
    
    // StartToBlueGoalNode->AddNext(EnableRingIntake);

    // wait to pick up rings before lowering lift
    // AutonNode* waitToLowerClaw = new AutonNode(3.0, new WaitAction(3.0));
    
    // StartToBlueGoalNode->AddNext(waitToLowerClaw);



    // 5b. Close Front Claw = Grab Second Goal
    // This is done as soon as the path to the yellow goal ends
    AutonNode* CloseFrontClaw1 = new AutonNode(0.1, new UseClawAction(m_frontClawNode, true));

    BlueGoalToYellowGoalNode->AddNext(CloseFrontClaw1);

    // Wait after close claw to raise it
    AutonNode* waitForClawClose = new AutonNode(0.5, new WaitAction(0.5));

    CloseFrontClaw1->AddNext(waitForClawClose);

    // 6b. Raise Second Goal to FULLY_UP
    AutonNode* RaiseGoal1 = new AutonNode(0.1, new SetLiftStateAction(m_liftNode, LiftNode::FULLY_UP));
    
    waitForClawClose->AddNext(RaiseGoal1);

    Path ToDropRed = PathManager::GetInstance()->GetPath("ToDropRed");
    AutonNode* ToDropRedNode = new AutonNode(10, new FollowPathAction(m_driveNode, m_odomNode, new TankPathPursuit(ToDropRed), ToDropRed, false));

    CloseFrontClaw1->AddNext(ToDropRedNode);

    AutonNode* OpenBackClaw2 = new AutonNode(0.1, new SetBackClawStateAction(m_backClaw, BackClawNode::PIVOT_DOWN_CLAW_OPEN));
    
    ToDropRedNode->AddNext(OpenBackClaw2);

    Path Forwards = PathManager::GetInstance()->GetPath("Forwards");
    AutonNode* ForwardsNode = new AutonNode(10, new FollowPathAction(m_driveNode, m_odomNode, new TankPathPursuit(Forwards), Forwards, false));

    ToDropRedNode->AddNext(ForwardsNode);

    AutonNode* OpenFrontClaw2 = new AutonNode(0.1, new UseClawAction(m_frontClawNode, false));

    ForwardsNode->AddNext(OpenFrontClaw2);

    Path UTurnGrabRed = PathManager::GetInstance()->GetPath("UTurnGrabRed");
    AutonNode* UTurnGrabRedNode = new AutonNode(10, new FollowPathAction(m_driveNode, m_odomNode, new TankPathPursuit(UTurnGrabRed), UTurnGrabRed, false));

    ForwardsNode->AddNext(UTurnGrabRedNode);

    AutonNode* CloseBackClaw2 = new AutonNode(0.1, new SetBackClawStateAction(m_backClaw, BackClawNode::PIVOT_BACK));

    UTurnGrabRedNode->AddNext(CloseBackClaw2);

    Path ScootToMiddle = PathManager::GetInstance()->GetPath("ScootToMiddle");
    AutonNode* ScootToMiddleNode = new AutonNode(10, new FollowPathAction(m_driveNode, m_odomNode, new TankPathPursuit(ScootToMiddle), ScootToMiddle, false));

    UTurnGrabRedNode->AddNext(ScootToMiddleNode);

    Path BackUp = PathManager::GetInstance()->GetPath("BackUp");
    AutonNode* BackUpNode = new AutonNode(10, new FollowPathAction(m_driveNode, m_odomNode, new TankPathPursuit(BackUp), BackUp, false));

    ScootToMiddleNode->AddNext(BackUpNode);

    AutonNode* LowerLift2 = new AutonNode(0.1, new SetLiftStateAction(m_liftNode, LiftNode::DOWN));
    
    BackUpNode->AddNext(LowerLift2);

    Path ForwardToMid = PathManager::GetInstance()->GetPath("ForwardToMid");
    AutonNode* ForwardToMidNode = new AutonNode(10, new FollowPathAction(m_driveNode, m_odomNode, new TankPathPursuit(ForwardToMid), ForwardToMid, false));

    BackUpNode->AddNext(ForwardToMidNode);

    AutonNode* CloseFrontClaw2 = new AutonNode(0.1, new UseClawAction(m_frontClawNode, true));

    ForwardToMidNode->AddNext(CloseFrontClaw2);

    AutonNode* wait34 = new AutonNode(0.5, new WaitAction(0.5));

    CloseFrontClaw2->AddNext(wait34);

    AutonNode* RaiseGoal2 = new AutonNode(0.1, new SetLiftStateAction(m_liftNode, LiftNode::UP_FOR_RINGS));
    
    wait34->AddNext(RaiseGoal2);

    Path BluePlat = PathManager::GetInstance()->GetPath("BluePlat");
    AutonNode* BluePlatNode = new AutonNode(10, new FollowPathAction(m_driveNode, m_odomNode, new TankPathPursuit(BluePlat), BluePlat, false));

    RaiseGoal2->AddNext(BluePlatNode);

    AutonNode* SpinToPosition = new AutonNode(5, new MoveSpinnerToPositionAction(m_goalSpinner, m_goalSpinner->getPosition() + 3200, 0));

    BluePlatNode->AddNext(SpinToPosition);

    AutonNode* HighRungLiftScore = new AutonNode(0.1, new SetHighRungLiftStateAction(m_highRungLiftNode, HighRungLiftNode::SCORING));
    
    SpinToPosition->AddNext(HighRungLiftScore);

    // // 7b. Path to Pre-Ring Intake Position
    // Path YellowToRings = PathManager::GetInstance()->GetPath("YellowToRings");
    // AutonNode* YellowToRingsNode = new AutonNode(10, new FollowPathAction(m_driveNode, m_odomNode, new TankPathPursuit(YellowToRings), YellowToRings, false));

    // BlueGoalToYellowGoalNode->AddNext(YellowToRingsNode);

    // // 9b. Path to Corner
    // Path ReverseTowardsBlueGoalDrop = PathManager::GetInstance()->GetPath("ReverseTowardsBlueGoalDrop");
    // AutonNode* ReverseTowardsBlueGoalDropNode = new AutonNode(10, new FollowPathAction(m_driveNode, m_odomNode, new TankPathPursuit(ReverseTowardsBlueGoalDrop), ReverseTowardsBlueGoalDrop, false));

    // YellowToRingsNode->AddNext(ReverseTowardsBlueGoalDropNode);

    // // Stop scoring rings
    // // Turn off conveyor
    // AutonNode* stopConveyor = new AutonNode(0.1, new RollerIntakeAction(m_conveyorNode, 0));
    
    // ReverseTowardsBlueGoalDropNode->AddNext(startConveyor);

    // // Turn off flap conveyor
    // AutonNode* stopFlapConveyor = new AutonNode(0.1, new RollerIntakeAction(m_flapConveyorNode, 0));
    
    // ReverseTowardsBlueGoalDropNode->AddNext(startFlapConveyor);

    // // 10b. Open Back Claw = Drop Goal
    // AutonNode* OpenBackClaw2 = new AutonNode(0.1, new SetBackClawStateAction(m_backClaw, BackClawNode::PIVOT_DOWN_CLAW_OPEN));

    // ReverseTowardsBlueGoalDropNode->AddNext(OpenBackClaw2);

};
