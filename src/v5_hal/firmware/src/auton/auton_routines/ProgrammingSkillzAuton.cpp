#include "auton/auton_routines/ProgrammingSkillzAuton.h"

ProgrammingSkillzAuton::ProgrammingSkillzAuton(IDriveNode* driveNode, OdometryNode* odomNode, IRollerIntakeNode* intakeNode, 
        IRollerIntakeNode* conveyorNode, IRollerIntakeNode* flapConveyorNode, IClawNode* frontClawNode, 
        BackClawNode* backClaw, IClawNode* wingArms, IClawNode* buddyClimb, LiftNode* liftNode, 
        HighRungLiftNode* highRungLiftNode) : 
        Auton("Programming Skills"), 
        m_driveNode(driveNode),
        m_odomNode(odomNode),
        m_intakeNode(intakeNode),
        m_conveyorNode(conveyorNode),
        m_flapConveyorNode(flapConveyorNode),
        m_frontClawNode(frontClawNode),
        m_backClaw(backClaw),
        m_wingArms(wingArms),
        m_buddyClimb(buddyClimb),
        m_liftNode(liftNode),
        m_highRungLiftNode(highRungLiftNode) {
    
}

void ProgrammingSkillzAuton::AddNodes() {
    // Set the starting position, as measured on the field
    // Pose startingPose(Vector2d(39, 14.3125), Rotation2Dd(M_PI_2));
    // m_odomNode->setCurrentPose(startingPose);

    AutonNode* deploy = new AutonNode(0.1, new DeployAction());
    Auton::AddFirstNode(deploy);

    // AutonNode* forward = new AutonNode(2, new DriveStraightAction(m_driveNode, m_odomNode, 40, 60, 1000));

    // deploy->AddNext(forward);

    // AutonNode* clawClose = new AutonNode(0.5, new UseClawAction(m_frontClawNode, false));

    // //Path path = PathManager::GetInstance()->GetPath("TestPath");
    // //AutonNode* testPath = new AutonNode(10, new FollowPathAction(m_driveNode, m_odomNode, new TankPathPursuit(path), path, false));

    // //forward -> AddNext(testPath);
    // forward -> AddNext(clawClose);

    // // AutonNode* clawOpen =new AutonNode(0.5, new UseClawAction(m_frontClawNode, true));

    // // Path NeutralToBluePath = PathManager::GetInstance()->GetPath("NeutralToBlue");
    // // AutonNode* NeutralToBlue = new AutonNode(10, new FollowPathAction(m_driveNode, m_odomNode, new TankPathPursuit(NeutralToBluePath), NeutralToBluePath, false));

    // // testPath -> AddNext(clawOpen);
    // // testPath -> AddNext(NeutralToBlue);

    // // AutonNode* clawClose2 =new AutonNode(0.5, new UseClawAction(m_frontClawNode, false));

    // // NeutralToBlue -> AddNext(clawClose2);

    // // AutonNode* LiftAction = new AutonNode(5, new MoveLiftToPositionAction(m_liftNode, 100, 20));

    // // Path BlueToMiddleNeutralPath = PathManager::GetInstance()->GetPath("BlueToMiddleNeutral");
    // // AutonNode* BlueToMiddleNeutral = new AutonNode(10, new FollowPathAction(m_driveNode, m_odomNode, new TankPathPursuit(BlueToMiddleNeutralPath), BlueToMiddleNeutralPath, false));

    // // AutonNode* startSuckingAndDontStop = new AutonNode(30, new RollerIntakeAction(m_intakeNode));

    // // clawClose2 ->AddNext(LiftAction);
    // // clawClose2 ->AddNext(startSuckingAndDontStop);
    // // clawClose2 ->AddNext(BlueToMiddleNeutral);

    // // Path MiddleNeutralToOurRingsPath = PathManager::GetInstance()->GetPath("MiddleNeutralToOurRings");
    // // AutonNode* MiddleNeutralToOurRings = new AutonNode(10, new FollowPathAction(m_driveNode, m_odomNode, new TankPathPursuit(MiddleNeutralToOurRingsPath), MiddleNeutralToOurRingsPath, false));


    // // // // START OF PART II (Asher Sprigler (spriglera@msoe.edu))

    //
    // Part 1: Move to reverse into the red goal holding down the platform
    AutonNode* releaseColorGoalCorner = new AutonNode(0.1, new SetBackClawStateAction(m_backClaw, BackClawNode::PIVOT_DOWN_CLAW_OPEN));

    deploy->AddNext(releaseColorGoalCorner);
    
    Path cornerToRedReversePointPath = PathManager::GetInstance() -> GetPath("CornerToRedReversePoint");
    AutonNode* cornerToRedReversePoint = new AutonNode(
        5,
        new FollowPathAction(
            m_driveNode,
            m_odomNode,
            new TankPathPursuit(cornerToRedReversePointPath),
            cornerToRedReversePointPath,
            true
        )
    );

    releaseColorGoalCorner->AddNext(cornerToRedReversePoint);

    //Part 2: Move to the goal holding down the platform, grab the goal

    Path midToRedRampPath = PathManager::GetInstance()->GetPath("MidToRedRamp");
    AutonNode* midToRedRamp = new AutonNode(
        5,
        new FollowPathAction(
            m_driveNode,
            m_odomNode,
            new TankPathPursuit(midToRedRampPath),
            midToRedRampPath,
            false
        )
    );

    cornerToRedReversePoint->AddNext(midToRedRamp);

    AutonNode* grabColorGoalCorner = new AutonNode(0.1, new SetBackClawStateAction(m_backClaw, BackClawNode::PIVOT_BACK));

    midToRedRamp->AddNext(grabColorGoalCorner);

    AutonNode* waitAfterColorGoalGrab = new AutonNode(0.5, new WaitAction(0.5));

    grabColorGoalCorner->AddNext(waitAfterColorGoalGrab);

    //Part 3: Lift the goal to ring height, turn on the conveyor belt,
    //Follow the path

    Path redRampToRedRingStopPath = PathManager::GetInstance()->GetPath("RedRampToRedRingStop");
    AutonNode* redRampToRedRingStop = new AutonNode(
        5,
        new FollowPathAction(
            m_driveNode,
            m_odomNode,
            new TankPathPursuit(redRampToRedRingStopPath),
            redRampToRedRingStopPath,
            false
        )
    );

    waitAfterColorGoalGrab->AddNext(redRampToRedRingStop);
    redRampToRedRingStop->AddAction(new SetLiftStateAction(m_liftNode, LiftNode::UP_FOR_RINGS));
    redRampToRedRingStop->AddAction(new RollerIntakeAction(m_intakeNode));
    redRampToRedRingStop->AddAction(new RollerIntakeAction(m_conveyorNode));
    redRampToRedRingStop->AddAction(new RollerIntakeAction(m_flapConveyorNode));
}