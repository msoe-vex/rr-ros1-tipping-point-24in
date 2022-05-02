#include "auton/auton_routines/ProgrammingSkillzAuton.h"

ProgrammingSkillzAuton::ProgrammingSkillzAuton(IDriveNode* driveNode, OdometryNode* odomNode, IRollerIntakeNode* intakeNode, 
        IRollerIntakeNode* conveyorNode, IRollerIntakeNode* flapConveyorNode, IClawNode* frontClawNode, 
        BackClawNode* backClaw, IClawNode* buddyClimb, LiftNode* liftNode, 
        HighRungLiftNode* highRungLiftNode) : 
        Auton("ProgSkills", "/usd/paths/path24inProgPt1v3.json"), 
        m_driveNode(driveNode),
        m_odomNode(odomNode),
        m_intakeNode(intakeNode),
        m_conveyorNode(conveyorNode),
        m_flapConveyorNode(flapConveyorNode),
        m_frontClawNode(frontClawNode),
        m_backClaw(backClaw),
        m_buddyClimb(buddyClimb),
        m_liftNode(liftNode),
        m_highRungLiftNode(highRungLiftNode) {
    
}

void ProgrammingSkillzAuton::AddNodes() {
    // Set the starting position, as measured on the field
    // Pose startingPose(Vector2d(38.4375, 13.625), Rotation2Dd(3.525));
    // m_odomNode->setCurrentPose(startingPose);
    // 1. Deploy
    AutonNode* deploy = new AutonNode(0.1, new DeployAction());
    Auton::AddFirstNode(deploy);
    
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

    // 3b. Close Back Claw= Grab First Goal
    AutonNode* CloseBackClaw1 = new AutonNode(0.1, new SetBackClawStateAction(m_backClaw, BackClawNode::PIVOT_BACK));

    StartToBlueGoalNode->AddNext(CloseBackClaw1);

    // 4b. Path to Second Goal
    Path BlueGoalToYellowGoal = PathManager::GetInstance()->GetPath("BlueGoalToYellowGoal");
    AutonNode* BlueGoalToYellowGoalNode = new AutonNode(10, new FollowPathAction(m_driveNode, m_odomNode, new TankPathPursuit(BlueGoalToYellowGoal), BlueGoalToYellowGoal, false));

    StartToBlueGoalNode->AddNext(BlueGoalToYellowGoalNode);

    // 4c. Open Front Claw
    AutonNode* OpenFrontClaw1 = new AutonNode(0.1, new UseClawAction(m_frontClawNode, false));

    StartToBlueGoalNode->AddNext(OpenFrontClaw1);

    // raise the goal above the rings
    AutonNode* RaiseLift = new AutonNode(0.1, new SetLiftStateAction(m_liftNode, LiftNode::UP_FOR_RINGS));
    
    StartToBlueGoalNode->AddNext(RaiseLift);

    //  Turn on Ring Intake
    AutonNode* EnableRingIntake = new AutonNode(0.1, new RollerIntakeAction(m_intakeNode));
    
    StartToBlueGoalNode->AddNext(EnableRingIntake);

    // wait to pick up rings before lowering lift
    AutonNode* waitToLowerClaw = new AutonNode(3.0, new WaitAction(3.0));
    
    StartToBlueGoalNode->AddNext(waitToLowerClaw);

    // Lower lift
    AutonNode* LowerLift = new AutonNode(0.1, new SetLiftStateAction(m_liftNode, LiftNode::DOWN));
    
    waitToLowerClaw->AddNext(LowerLift);

    // 5b. Close Front Claw = Grab Second Goal
    AutonNode* CloseFrontClaw1 = new AutonNode(0.1, new UseClawAction(m_frontClawNode, true));

    BlueGoalToYellowGoalNode->AddNext(CloseFrontClaw1);

    // Wait after close claw to raise it
    AutonNode* waitForClawClose = new AutonNode(0.5, new WaitAction(0.5));

    CloseFrontClaw1->AddNext(waitForClawClose);

    // 6b. Raise Second Goal
    AutonNode* RaiseGoal1 = new AutonNode(0.1, new SetLiftStateAction(m_liftNode, LiftNode::UP_FOR_RINGS));
    
    waitForClawClose->AddNext(RaiseGoal1);

    // 7b. Path to Pre-Ring Intake Position
    Path YellowToRings = PathManager::GetInstance()->GetPath("YellowToRings");
    AutonNode* YellowToRingsNode = new AutonNode(10, new FollowPathAction(m_driveNode, m_odomNode, new TankPathPursuit(YellowToRings), YellowToRings, false));

    BlueGoalToYellowGoalNode->AddNext(YellowToRingsNode);

    // 8b. Path to Ring Cluster
    // Path PathToRingCluster = PathManager::GetInstance()->GetPath("LeftGoalToWallReverse");
    // AutonNode* PathToRingClusterNode = new AutonNode(10, new FollowPathAction(m_driveNode, m_odomNode, new TankPathPursuit(PathToRingCluster), PathToRingCluster, false));

    // YellowToRingsNode->AddNext(PathToRingClusterNode);

    // // 9b. Path to Corner
    // Path PathToCorner = PathManager::GetInstance()->GetPath("LeftGoalToWallReverse");
    // AutonNode* PathToCornerNode = new AutonNode(10, new FollowPathAction(m_driveNode, m_odomNode, new TankPathPursuit(PathToCorner), PathToCorner, false));

    // PathToRingClusterNode->AddNext(PathToCornerNode);

    // // 9c. Turn off Ring Intake
    // AutonNode* DisableRingIntake = new AutonNode(0.1, new RollerIntakeAction(m_intakeNode, 0));
    
    // PathToRingClusterNode->AddNext(DisableRingIntake);

    // // 10b. Open Back Claw = Drop Goal
    // AutonNode* OpenBackClaw2 = new AutonNode(0.1, new SetBackClawStateAction(m_backClaw, BackClawNode::PIVOT_DOWN_CLAW_OPEN));

    // PathToFirstGoalNode->AddNext(OpenBackClaw2);

};
