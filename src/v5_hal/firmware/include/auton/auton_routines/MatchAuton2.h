#pragma once

#include "lib-rr/auton/Auton.h"
#include "lib-rr/nodes/subsystems/IDriveNode.h"
#include "lib-rr/nodes/odometry_nodes/OdometryNode.h"
#include "lib-rr/nodes/sensor_nodes/InertialSensorNode.h"
#include "lib-rr/auton/auton_actions/DriveStraightAction.h"
#include "auton/auton_actions/PlatformBalance.h"
#include "auton/auton_actions/SetLiftStateAction.h"
#include "lib-rr/auton/auton_actions/UseClawAction.h"
#include "lib-rr/auton/auton_actions/MoveLiftToPositionAction.h"
#include "lib-rr/nodes/subsystems/ILiftNode.h"
#include "lib-rr/nodes/subsystems/IClawNode.h"
#include "auton/auton_actions/DeployAction.h"
#include "lib-rr/util/Constants.h"
#include "lib-rr/eigen/Eigen/Dense"
#include "nodes/LiftNode.h"

class MatchAuton2 : public Auton {
public:
    MatchAuton2(IDriveNode* drive_node, OdometryNode* odom_node, IClawNode* front_claw_node, LiftNode* liftNode);

    void AddNodes();

private:
    IDriveNode* m_drive_node;
    ADIEncoderNode* m_y_odom_encoder;
    InertialSensorNode* m_inertial_sensor;
    OdometryNode* m_odom_node;
    IClawNode* m_front_claw_node;
    LiftNode* m_liftNode;
};