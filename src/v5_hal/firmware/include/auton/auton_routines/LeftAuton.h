#pragma once

#include "lib-rr/auton/Auton.h"
#include "lib-rr/nodes/subsystems/IDriveNode.h"
#include "lib-rr/nodes/odometry_nodes/OdometryNode.h"
#include "lib-rr/nodes/sensor_nodes/InertialSensorNode.h"
#include "lib-rr/auton/auton_actions/DriveStraightAction.h"
#include "auton/auton_actions/PlatformBalance.h"
#include "auton/auton_actions/SetLiftStateAction.h"
#include "auton/auton_actions/SetBackClawStateAction.h"
#include "auton/auton_actions/SetHighRungLiftStateAction.h"
#include "lib-rr/auton/auton_actions/UseClawAction.h"
#include "lib-rr/auton/auton_actions/MoveLiftToPositionAction.h"
#include "lib-rr/auton/auton_actions/RollerIntakeAction.h"
#include "lib-rr/auton/auton_actions/FollowPathAction.h"
#include "lib-rr/pursuit/path_pursuit/TankPathPursuit.h"
#include "lib-rr/nodes/subsystems/ILiftNode.h"
#include "lib-rr/nodes/subsystems/IClawNode.h"
#include "auton/auton_actions/DeployAction.h"
#include "lib-rr/util/Constants.h"
#include "lib-rr/eigen/Eigen/Dense"
#include "nodes/LiftNode.h"
#include "lib-rr/pathing/PathManager.h"
#include "utils/Constants.h"

class LeftAuton : public Auton {
public:
    LeftAuton(IDriveNode* drive_node, OdometryNode* odom_node, IClawNode* front_claw_node, 
        LiftNode* liftNode, HighRungLiftNode* highRingLiftNode, BackClawNode* backClawNode, IRollerIntakeNode* intakeNode,
        IRollerIntakeNode* conveyorNode, IRollerIntakeNode* flapConveyorNode);

    void AddNodes();

private:
    IDriveNode* m_drive_node;
    ADIEncoderNode* m_y_odom_encoder;
    InertialSensorNode* m_inertial_sensor;
    OdometryNode* m_odom_node;
    IClawNode* m_front_claw_node;
    LiftNode* m_liftNode;
    HighRungLiftNode* m_highRungLiftNode;
    BackClawNode* m_backClawNode;
    IRollerIntakeNode* m_intakeNode;
    IRollerIntakeNode* m_conveyorNode;
    IRollerIntakeNode* m_flapConveyorNode;
};