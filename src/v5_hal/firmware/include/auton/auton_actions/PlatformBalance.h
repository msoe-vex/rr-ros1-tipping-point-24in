#pragma once

#include "lib-rr/auton/Auton.h"
#include "lib-rr/util/Timer.h"
#include "lib-rr/nodes/subsystems/IDriveNode.h"
#include "lib-rr/nodes/sensor_nodes/InertialSensorNode.h"
#include "lib-rr/auton/auton_actions/DriveStraightAction.h"
#include "lib-rr/nodes/sensor_nodes/ADIEncoderNode.h"


class PlatformBalance : public AutonAction {
private:
    Timer m_timer;

public:
    PlatformBalance(IDriveNode* drive_node, ADIEncoderNode* encoder_node, InertialSensorNode* inertial_node);

    void ActionInit();

    actionStatus Action();
    
    void ActionEnd();
};
