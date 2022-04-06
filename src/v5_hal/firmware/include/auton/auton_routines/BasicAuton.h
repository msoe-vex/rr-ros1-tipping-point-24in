#pragma once

#include "lib-rr/auton/Auton.h"
#include "lib-rr/nodes/subsystems/IDriveNode.h"
#include "lib-rr/nodes/sensor_nodes/InertialSensorNode.h"
#include "lib-rr/auton/auton_actions/DriveStraightAction.h"
#include "auton/auton_actions/PlatformBalance.h"
#include "lib-rr/auton/auton_actions/UseClawAction.h"
#include "lib-rr/auton/auton_actions/MoveLiftToPositionAction.h"
#include "lib-rr/nodes/subsystems/ILiftNode.h"
#include "lib-rr/nodes/subsystems/IClawNode.h"
#include "lib-rr/util/Constants.h"
#include "lib-rr/eigen/Eigen/Dense"

class BasicAuton : public Auton {
public:
    //BasicAuton(IDriveNode* drive_node);
    BasicAuton(IDriveNode* drive_node, OdometryNode* odom_node);

    void AddNodes();

private:
    IDriveNode* m_drive_node;
    OdometryNode* m_odom_node

};