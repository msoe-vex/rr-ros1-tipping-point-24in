#include "auton/auton_routines/MatchAuton.h"

MatchAuton::MatchAuton(IDriveNode* drive_node, OdometryNode* odom_node, IClawNode* front_claw_node, ILiftNode* lift_node, IRollerIntakeNode* intake_node) : 
        Auton("Test Turn Node"), 
        m_driveNode(drive_node),
        m_odomNode(odom_node),
        m_frontClawNode(front_claw_node),
        m_liftNode(lift_node),
        m_intakeNode(intake_node) {
    
}

void MatchAuton::AddNodes() {
    // Set the starting position, as measured on the field
    Pose startingPose(Vector2d(-44.75, 16.75), Rotation2Dd(1.449));
    m_odomNode->setCurrentPose(startingPose);

    AutonNode* deploy = new AutonNode(0.1, new DeployAction());
    Auton::AddFirstNode(deploy);

    AutonNode* forward = new AutonNode(2, new DriveStraightAction(m_driveNode, m_odomNode, 38, 70, 80));

    AutonNode* clawCloseDelay = new AutonNode(1.2, new WaitAction(1.2));

    deploy->AddNext(forward);
    deploy->AddNext(clawCloseDelay);

    AutonNode* clawClose = new AutonNode(0.5, new UseClawAction(m_frontClawNode, true));
    clawCloseDelay ->AddNext(clawClose);

    AutonNode* wait = new AutonNode(0.5, new WaitAction(0.5));

    Path path = PathManager::GetInstance()->GetPath("TestPath");
    AutonNode* testPath = new AutonNode(10, new FollowPathAction(m_driveNode, m_odomNode, new TankPathPursuit(path), path, false));

    forward -> AddNext(testPath);

    AutonNode* clawOpen =new AutonNode(0.5, new UseClawAction(m_frontClawNode, false));

    Path NeutralToBluePath = PathManager::GetInstance()->GetPath("NeutralToBlue");
    AutonNode* NeutralToBlue = new AutonNode(10, new FollowPathAction(m_driveNode, m_odomNode, new TankPathPursuit(NeutralToBluePath), NeutralToBluePath, false));

    testPath -> AddNext(clawOpen);
    testPath -> AddNext(NeutralToBlue);

    AutonNode* clawClose2 =new AutonNode(0.5, new UseClawAction(m_frontClawNode, true));

    NeutralToBlue -> AddNext(clawClose2);

    AutonNode* LiftAction = new AutonNode(5, new MoveLiftToPositionAction(m_liftNode, 100, 20));

    Path BlueToMiddleNeutralPath = PathManager::GetInstance()->GetPath("BlueToMiddleNeutral");
    AutonNode* BlueToMiddleNeutral = new AutonNode(10, new FollowPathAction(m_driveNode, m_odomNode, new TankPathPursuit(BlueToMiddleNeutralPath), BlueToMiddleNeutralPath, false));

    AutonNode* startSuckingAndDontStop = new AutonNode(30, new RollerIntakeAction(m_intakeNode));

    clawClose2 ->AddNext(LiftAction);
    clawClose2 ->AddNext(startSuckingAndDontStop);
    clawClose2 ->AddNext(BlueToMiddleNeutral);

    Path MiddleNeutralToOurRingsPath = PathManager::GetInstance()->GetPath("MiddleNeutralToOurRings");
    AutonNode* MiddleNeutralToOurRings = new AutonNode(10, new FollowPathAction(m_driveNode, m_odomNode, new TankPathPursuit(MiddleNeutralToOurRingsPath), MiddleNeutralToOurRingsPath, false));





}