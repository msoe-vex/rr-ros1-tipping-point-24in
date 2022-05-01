#include "auton/auton_routines/MatchAuton2.h"

MatchAuton2::MatchAuton2(IDriveNode* drive_node, OdometryNode* odom_node, IClawNode* front_claw_node, LiftNode* liftNode) : 
        Auton("Test Turn Node"), 
        m_drive_node(drive_node),
        m_odom_node(odom_node),
        m_front_claw_node(front_claw_node),
        m_liftNode(liftNode) {
    
}

void MatchAuton2::AddNodes() {
    // Set the starting position, as measured on the field
    Pose startingPose(Vector2d(-46, 11.375), Rotation2Dd(toRadians(92)));
    m_odom_node->setCurrentPose(startingPose);

    AutonNode* deploy = new AutonNode(0.1, new DeployAction());
    Auton::AddFirstNode(deploy);

    AutonNode* forward = new AutonNode(2, new DriveStraightAction(m_drive_node, m_odom_node, 33, 70, 80));
    deploy->AddNext(forward);

    AutonNode* lowerLift = new AutonNode(2, new SetLiftStateAction(m_liftNode, LiftNode::LiftState::DOWN));
    deploy->AddNext(lowerLift);

    AutonNode* clawCloseDelay = new AutonNode(1.2, new WaitAction(1.2));
    deploy->AddNext(clawCloseDelay);
    
    AutonNode* clawClose = new AutonNode(0.5, new UseClawAction(m_front_claw_node, true));
    clawCloseDelay->AddNext(clawClose);

    Path path = PathManager::GetInstance()->GetPath("FirstBacking");
    AutonNode* driveBackFromYellowGoal = new AutonNode(10, new FollowPathAction(m_drive_node, m_odom_node, new TankPathPursuit(path), path, false));
    clawClose->AddNext(driveBackFromYellowGoal);
    
    AutonNode* clawOpen = new AutonNode(0.5, new UseClawAction(m_front_claw_node, false));
    driveBackFromYellowGoal->AddNext(clawOpen);
    
    // AutonNode* backClawOpen = new AutonNode(0.5, new UseClawAction(m_front_claw_node, false));
    // driveBackFromYellowGoal->AddNext(clawOpen);
}