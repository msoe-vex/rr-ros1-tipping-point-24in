#pragma once

#include "lib-rr/auton/Auton.h"
#include "lib-rr/nodes/subsystems/IDriveNode.h"
#include "lib-rr/nodes/sensor_nodes/InertialSensorNode.h"
#include "lib-rr/auton/auton_actions/DriveStraightAction.h"
#include "lib-rr/auton/auton_actions/UseClawAction.h"
#include "lib-rr/util/Constants.h"
#include "lib-rr/eigen/Eigen/Dense"

class BasicAuton : public Auton {
public:
    BasicAuton(IDriveNode* drive_node, IClawNode* claw_node);

    void AddNodes();

private:
    IDriveNode* m_drive_node;
    IClawNode* m_claw_node;

    AutonNode* m_forward_node;
    AutonNode* m_claw_close_node;
    AutonNode* m_backward_node;
};