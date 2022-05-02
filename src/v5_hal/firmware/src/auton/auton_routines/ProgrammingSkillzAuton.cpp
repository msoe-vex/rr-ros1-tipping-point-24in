#include "auton/auton_routines/ProgrammingSkillzAuton.h"

ProgrammingSkillzAuton::ProgrammingSkillzAuton(IDriveNode* driveNode, OdometryNode* odomNode, IRollerIntakeNode* intakeNode, 
        IRollerIntakeNode* conveyorNode, IRollerIntakeNode* flapConveyorNode, IClawNode* frontClawNode, 
        BackClawNode* backClaw, IClawNode* buddyClimb, LiftNode* liftNode, 
        HighRungLiftNode* highRungLiftNode) : 
        Auton("Test Turn Node"), 
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
    Pose startingPose(Vector2d(35.1875, 13.625), Rotation2Dd(3.525));
    m_odomNode->setCurrentPose(startingPose);
    // 1. Deploy
    AutonNode* deploy = new AutonNode(0.1, new DeployAction());
    Auton::AddFirstNode(deploy);
    
    // 2a. Open Back Claw
    AutonNode* OpenBackClaw1 = new AutonNode(0.1, new SetBackClawStateAction(m_backClaw,BackClawNode::PIVOT_DOWN_CLAW_OPEN));
    
    deploy->AddNext(OpenBackClaw1);

    // 2b. Path to First Goal
    Path PathToFirstGoal = PathManager::GetInstance()->GetPath("LeftGoalToWallReverse");
    AutonNode* PathToFirstGoalNode = new AutonNode(10, new FollowPathAction(m_driveNode, m_odomNode, new TankPathPursuit(PathToFirstGoal), PathToFirstGoal, false));

    deploy->AddNext(PathToFirstGoalNode);

    // 3b. Close Back Claw
    AutonNode* CloseBackClaw1 = new AutonNode(0.1, new SetBackClawStateAction(m_backClaw, BackClawNode::PIVOT_BACK));

    PathToFirstGoalNode->AddNext(CloseBackClaw1);

    // 4b. Path to Second Goal
    Path PathToSecondGoal = PathManager::GetInstance()->GetPath("LeftGoalToWallReverse");
    AutonNode* PathToSecondGoalNode = new AutonNode(10, new FollowPathAction(m_driveNode, m_odomNode, new TankPathPursuit(PathToSecondGoal), PathToSecondGoal, false));

    CloseBackClaw1->AddNext(PathToSecondGoalNode);

    // 4c. Open Front Claw
    AutonNode* OpenFrontClaw1 = new AutonNode(0.1, new UseClawAction(m_frontClawNode, false));

    CloseBackClaw1->AddNext(OpenFrontClaw1);

    // 5b. Close Front Claw
    AutonNode* CloseFrontClaw1 = new AutonNode(0.1, new UseClawAction(m_frontClawNode, true));

    PathToSecondGoalNode->AddNext(CloseFrontClaw1);

    // 6b. Raise Goal
    
    AutonNode* RaiseGoal1 = new AutonNode(0.1, new SetLiftStateAction(m_liftNode, LiftNode::FULLY_UP));
    
    CloseFrontClaw1->AddNext(RaiseGoal1);

    // 7b. Path to Pre-Ring Intake Position

    Path PathToPreRingIntake = PathManager::GetInstance()->GetPath("LeftGoalToWallReverse");
    AutonNode* PathToPreRingIntakeNode = new AutonNode(10, new FollowPathAction(m_driveNode, m_odomNode, new TankPathPursuit(PathToPreRingIntake), PathToPreRingIntake, false));

    CloseFrontClaw1->AddNext(PathToPreRingIntakeNode);

    // 7d. Turn on Ring Intake

    //AutonNode* RaiseGoal1 = new AutonNode(0.1, new SetLiftStateAction(m_liftNode, LiftNode::FULLY_UP));
    
    //CloseFrontClaw1->AddNext(RaiseGoal1);

    // 8b. Path to Ring Cluster

    // 9b. Path to Corner
    // 9c. Turn off Ring Intake
    // 10b. Drop Goal


    

   

    // AutonNode* clawClose = new AutonNode(0.5, new UseClawAction(m_frontClawNode, false));

    // Path path = PathManager::GetInstance()->GetPath("TestPath");
    // AutonNode* testPath = new AutonNode(10, new FollowPathAction(m_driveNode, m_odomNode, new TankPathPursuit(path), path, false));

    // //forward -> AddNext(testPath);
    // forward -> AddNext(clawClose);

    // AutonNode* clawOpen =new AutonNode(0.5, new UseClawAction(m_frontClawNode, true));

    // Path NeutralToBluePath = PathManager::GetInstance()->GetPath("NeutralToBlue");
    // AutonNode* NeutralToBlue = new AutonNode(10, new FollowPathAction(m_driveNode, m_odomNode, new TankPathPursuit(NeutralToBluePath), NeutralToBluePath, false));

    // testPath -> AddNext(clawOpen);
    // testPath -> AddNext(NeutralToBlue);

    // AutonNode* clawClose2 =new AutonNode(0.5, new UseClawAction(m_frontClawNode, false));

    // NeutralToBlue -> AddNext(clawClose2);

    // AutonNode* LiftAction = new AutonNode(5, new MoveLiftToPositionAction(m_liftNode, 100, 20));

    // Path BlueToMiddleNeutralPath = PathManager::GetInstance()->GetPath("BlueToMiddleNeutral");
    // AutonNode* BlueToMiddleNeutral = new AutonNode(10, new FollowPathAction(m_driveNode, m_odomNode, new TankPathPursuit(BlueToMiddleNeutralPath), BlueToMiddleNeutralPath, false));

    // AutonNode* startSuckingAndDontStop = new AutonNode(30, new RollerIntakeAction(m_intakeNode));

    // clawClose2 ->AddNext(LiftAction);
    // clawClose2 ->AddNext(startSuckingAndDontStop);
    // clawClose2 ->AddNext(BlueToMiddleNeutral);

    // Path MiddleNeutralToOurRingsPath = PathManager::GetInstance()->GetPath("MiddleNeutralToOurRings");
    // AutonNode* MiddleNeutralToOurRings = new AutonNode(10, new FollowPathAction(m_driveNode, m_odomNode, new TankPathPursuit(MiddleNeutralToOurRingsPath), MiddleNeutralToOurRingsPath, false));





};