#include "auton/auton_routines/MatchAuton2.h"

MatchAuton2::MatchAuton2(IDriveNode* drive_node, OdometryNode* odom_node, ADIEncoderNode* y_odom_encoder, InertialSensorNode* inertial_sensor, IClawNode* front_claw_node) : 
        Auton("Test Turn Node"), 
        m_drive_node(drive_node),
        m_odom_node(odom_node),
        m_front_claw_node(front_claw_node) {
    
}

void MatchAuton2::AddNodes() {
    // Set the starting position, as measured on the field
    Pose startingPose(Vector2d(-44.75, 16.75), Rotation2Dd(1.449));
    m_odom_node->setCurrentPose(startingPose);

    AutonNode* deploy = new AutonNode(0.1, new DeployAction());
    Auton::AddFirstNode(deploy);

    AutonNode* forward = new AutonNode(2, new DriveStraightAction(m_drive_node, m_odom_node, 38, 70, 80));

    AutonNode* clawCloseDelay = new AutonNode(1.2, new WaitAction(1.2));

    deploy->AddNext(forward);
    deploy->AddNext(clawCloseDelay);

    AutonNode* clawClose = new AutonNode(0.5, new UseClawAction(m_front_claw_node, true));
    clawCloseDelay ->AddNext(clawClose);


}