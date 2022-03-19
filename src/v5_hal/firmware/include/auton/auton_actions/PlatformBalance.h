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
    IDriveNode* m_drive_node;
    InertialSensorNode* m_inertial_node;
    ADIEncoderNode* m_encoder_node;
    Eigen::Rotation2Dd m_roll;
    Eigen::Rotation2Dd m_roll_offset;
    double m_roll_true;
    int m_phase = 1;

public:
    PlatformBalance(IDriveNode* drive_node, ADIEncoderNode* encoder_node, InertialSensorNode* inertial_node);

    void ActionInit();

    actionStatus Action();
    
    void ActionEnd();
};
