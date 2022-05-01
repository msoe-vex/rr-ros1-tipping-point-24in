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
    // Pose startingPose(Vector2d(39, 14.3125), Rotation2Dd(M_PI_2));
    // m_odomNode->setCurrentPose(startingPose);

    // AutonNode* deploy = new AutonNode(0.1, new DeployAction());
    // Auton::AddFirstNode(deploy);

    // AutonNode* forward = new AutonNode(2, new DriveStraightAction(m_driveNode, m_odomNode, DRIVE_PARAMS, 40, 60, 1000));

    // deploy->AddNext(forward);

    // AutonNode* clawClose = new AutonNode(0.5, new UseClawAction(m_frontClawNode, false));

    // //Path path = PathManager::GetInstance()->GetPath("TestPath");
    // //AutonNode* testPath = new AutonNode(10, new FollowPathAction(m_driveNode, m_odomNode, new TankPathPursuit(path), path, false));

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





}