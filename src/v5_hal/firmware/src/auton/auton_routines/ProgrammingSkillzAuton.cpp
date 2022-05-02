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

    // 3b. Close Back Claw= Grab First Goal
    AutonNode* CloseBackClaw1 = new AutonNode(0.1, new SetBackClawStateAction(m_backClaw, BackClawNode::PIVOT_BACK));

    PathToFirstGoalNode->AddNext(CloseBackClaw1);

    // 4b. Path to Second Goal
    Path PathToSecondGoal = PathManager::GetInstance()->GetPath("LeftGoalToWallReverse");
    AutonNode* PathToSecondGoalNode = new AutonNode(10, new FollowPathAction(m_driveNode, m_odomNode, new TankPathPursuit(PathToSecondGoal), PathToSecondGoal, false));

    CloseBackClaw1->AddNext(PathToSecondGoalNode);

    // 4c. Open Front Claw
    AutonNode* OpenFrontClaw1 = new AutonNode(0.1, new UseClawAction(m_frontClawNode, false));

    CloseBackClaw1->AddNext(OpenFrontClaw1);

    // 5b. Close Front Claw = Grab Second Goal
    AutonNode* CloseFrontClaw1 = new AutonNode(0.1, new UseClawAction(m_frontClawNode, true));

    PathToSecondGoalNode->AddNext(CloseFrontClaw1);

    // 6b. Raise Second Goal
    AutonNode* RaiseGoal1 = new AutonNode(0.1, new SetLiftStateAction(m_liftNode, LiftNode::FULLY_UP));
    
    CloseFrontClaw1->AddNext(RaiseGoal1);

    // 7b. Path to Pre-Ring Intake Position
    Path PathToPreRingIntake = PathManager::GetInstance()->GetPath("LeftGoalToWallReverse");
    AutonNode* PathToPreRingIntakeNode = new AutonNode(10, new FollowPathAction(m_driveNode, m_odomNode, new TankPathPursuit(PathToPreRingIntake), PathToPreRingIntake, false));

    RaiseGoal1->AddNext(PathToPreRingIntakeNode);

    // 7d. Turn on Ring Intake
    AutonNode* EnableRingIntake = new AutonNode(0.1, new RollerIntakeAction(m_intakeNode));
    
    RaiseGoal1->AddNext(EnableRingIntake);

    // 8b. Path to Ring Cluster
    Path PathToRingCluster = PathManager::GetInstance()->GetPath("LeftGoalToWallReverse");
    AutonNode* PathToRingClusterNode = new AutonNode(10, new FollowPathAction(m_driveNode, m_odomNode, new TankPathPursuit(PathToRingCluster), PathToRingCluster, false));

    PathToPreRingIntakeNode->AddNext(PathToRingClusterNode);

    // 9b. Path to Corner
    Path PathToCorner = PathManager::GetInstance()->GetPath("LeftGoalToWallReverse");
    AutonNode* PathToCornerNode = new AutonNode(10, new FollowPathAction(m_driveNode, m_odomNode, new TankPathPursuit(PathToCorner), PathToCorner, false));

    PathToRingClusterNode->AddNext(PathToCornerNode);

    // 9c. Turn off Ring Intake
    AutonNode* DisableRingIntake = new AutonNode(0.1, new RollerIntakeAction(m_intakeNode, 0));
    
    PathToRingClusterNode->AddNext(DisableRingIntake);

    // 10b. Open Back Claw = Drop Goal
    AutonNode* OpenBackClaw2 = new AutonNode(0.1, new SetBackClawStateAction(m_backClaw, BackClawNode::PIVOT_DOWN_CLAW_OPEN));

    PathToFirstGoalNode->AddNext(OpenBackClaw2);

};