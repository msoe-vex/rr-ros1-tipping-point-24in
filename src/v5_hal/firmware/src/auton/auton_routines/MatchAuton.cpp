#include "auton/auton_routines/MatchAuton.h"

MatchAuton::MatchAuton(IDriveNode* drive_node, OdometryNode* odom_node, IClawNode* front_claw_node) : 
        Auton("Test Turn Node"), 
        m_driveNode(drive_node),
        m_odomNode(odom_node),
        m_frontClawNode(front_claw_node) {
    
}

void MatchAuton::AddNodes() {
    // Set the starting position, as measured on the field
    Pose startingPose(Vector2d(-44.75, 16.75), Rotation2Dd(1.449));
    m_odomNode->setCurrentPose(startingPose);

    AutonNode* deploy = new AutonNode(0.1, new DeployAction());
    Auton::AddFirstNode(deploy);

    AutonNode* forward = new AutonNode(2, new DriveStraightAction(m_driveNode, m_odomNode, DRIVE_PARAMS, 38., 70., 80.));

    AutonNode* clawCloseDelay = new AutonNode(1.2, new WaitAction(1.2));

    deploy->AddNext(forward);
    deploy->AddNext(clawCloseDelay);

    AutonNode* clawClose = new AutonNode(0.5, new UseClawAction(m_frontClawNode, true));
    clawCloseDelay ->AddNext(clawClose);


}