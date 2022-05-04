#include "auton/auton_routines/ProgrammingSkillzAuton.h"

ProgrammingSkillzAuton::ProgrammingSkillzAuton(IDriveNode* driveNode, OdometryNode* odomNode, IRollerIntakeNode* intakeNode, 
        IRollerIntakeNode* conveyorNode, IRollerIntakeNode* flapConveyorNode, IClawNode* frontClawNode, 
        BackClawNode* backClaw, IClawNode* wingArms, IClawNode* buddyClimb, LiftNode* liftNode, 
        HighRungLiftNode* highRungLiftNode):
        Auton("Programming Skills", "/usd/paths/path24inProgPt2.json"), 
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

   //Part 3: Move to the middle neutral goal, raise lift, conveyor, front ring roller, flaps, and agitator

    Path redRampToCenterGoalPath = PathManager::GetInstance()->GetPath("RedRampToCenterGoal");
    AutonNode* redRampToCenterGoal = new AutonNode(
        5,
        new FollowPathAction(
            m_driveNode,
            m_odomNode,
            new TankPathPursuit(redRampToCenterGoalPath),
            redRampToCenterGoalPath,
            false
        )
    );

    waitAfterColorGoalGrab->AddNext(redRampToCenterGoal);
    redRampToCenterGoal->AddAction(new SetLiftStateAction(m_liftNode, LiftNode::UP_FOR_RINGS));
    redRampToCenterGoal->AddAction(new RollerIntakeAction(m_intakeNode));
    redRampToCenterGoal->AddAction(new RollerIntakeAction(m_conveyorNode));
    redRampToCenterGoal->AddAction(new RollerIntakeAction(m_flapConveyorNode));

    //Part 4: Backup up, lift down, turn off front roller, close claw

    Path centerGoalDragBackPath = PathManager::GetInstance()->GetPath("CenterGoalDragBack");
    AutonNode* centerGoalDragBack = new AutonNode(
        5,
        new FollowPathAction(
            m_driveNode,
            m_odomNode,
            new TankPathPursuit(centerGoalDragBackPath),
            centerGoalDragBackPath,
            false
        )
    );
    
    redRampToCenterGoal->AddNext(centerGoalDragBack);
    centerGoalDragBack->AddAction(new SetLiftStateAction(m_liftNode, LiftNode::DOWN));

    AutonNode* clawCloseMid = new AutonNode(0.5, new UseClawAction(m_frontClawNode, false));
    redRampToCenterGoal->AddNext(clawCloseMid);
    centerGoalDragBack->AddAction(new RollerIntakeAction(m_intakeNode, 0));

    //Part 5: Claw open and drive forward

    Path centerGoalForwardGrabPath = PathManager::GetInstance()->GetPath("CenterGoalForwardGrab");
    AutonNode* centerGoalForwardGrab = new AutonNode(
        5,
        new FollowPathAction(
            m_driveNode,
            m_odomNode,
            new TankPathPursuit(centerGoalForwardGrabPath),
            centerGoalForwardGrabPath,
            false
        )
    );

    centerGoalDragBack->AddNext(centerGoalForwardGrab);
    AutonNode* clawOpenMid = new AutonNode(0.5, new UseClawAction(m_frontClawNode, true));
    centerGoalDragBack->AddNext(clawOpenMid);

    AutonNode* clawCloseMid = new AutonNode(0.5, new UseClawAction(m_frontClawNode, false));
    centerGoalForwardGrab->AddNext(clawCloseMid);

    //Part 6: Drive to Ramp, intake, Lift up

    Path centerGoalToOppositeRampPath = PathManager::GetInstance()->GetPath("CenterGoalToOppositeRamp");
    AutonNode* centerGoalToOppositeRamp = new AutonNode(
        5,
        new FollowPathAction(
            m_driveNode,
            m_odomNode,
            new TankPathPursuit(centerGoalForwardGrabPath),
            centerGoalForwardGrabPath,
            false
        )
    );

    AutonNode* waitAfterNeutralGrab = new AutonNode(0.5, new WaitAction(0.5));
    centerGoalForwardGrab->AddNext(centerGoalToOppositeRamp);
    centerGoalForwardGrab->AddNext(waitAfterNeutralGrab);
    centerGoalToOppositeRamp->AddAction(new SetLiftStateAction(m_liftNode, LiftNode::UP_FOR_RINGS));
    centerGoalToOppositeRamp->AddAction(new RollerIntakeAction(m_intakeNode));

    AutonNode* stopRoller = new AutonNode(0.5, new RollerIntakeAction(m_intakeNode, 0));
    centerGoalToOppositeRamp->AddNext(stopRoller);

    AutonNode* stopConv = new AutonNode(0.5, new RollerIntakeAction(m_conveyorNode, 0));
    centerGoalToOppositeRamp->AddNext(stopConv);
    AutonNode* stopFlapConv = new AutonNode(0.5, new RollerIntakeAction(m_flapConveyorNode, 0));
    centerGoalToOppositeRamp->AddNext(stopFlapConv);

}
