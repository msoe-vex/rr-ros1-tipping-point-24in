#pragma once

#include "lib-rr/auton/Auton.h"
#include "lib-rr/nodes/subsystems/IDriveNode.h"
#include "lib-rr/nodes/odometry_nodes/OdometryNode.h"
#include "lib-rr/nodes/sensor_nodes/InertialSensorNode.h"
#include "lib-rr/auton/auton_actions/DriveStraightAction.h"
#include "auton/auton_actions/PlatformBalance.h"
#include "lib-rr/auton/auton_actions/UseClawAction.h"
#include "lib-rr/auton/auton_actions/MoveLiftToPositionAction.h"
#include "lib-rr/auton/auton_actions/RollerIntakeAction.h"
#include "lib-rr/auton/auton_actions/FollowPathAction.h"
#include "lib-rr/pursuit/path_pursuit/TankPathPursuit.h"
#include "lib-rr/nodes/subsystems/ILiftNode.h"
#include "lib-rr/nodes/subsystems/IClawNode.h"
#include "auton/auton_actions/DeployAction.h"
#include "lib-rr/pathing/PathManager.h"
#include "lib-rr/math/Pose.h"
#include "lib-rr/util/Constants.h"
#include "lib-rr/eigen/Eigen/Dense"

class MatchAuton : public Auton {
public:
    MatchAuton(IDriveNode* drive_node, OdometryNode* odom_node, IClawNode* front_claw_node, ILiftNode* lift_node, IRollerIntakeNode* intake_node);

    void AddNodes();

private:
    IDriveNode* m_driveNode;
    OdometryNode* m_odomNode;
    IClawNode* m_frontClawNode;
    ILiftNode* m_liftNode;
    IRollerIntakeNode* m_intakeNode;

};