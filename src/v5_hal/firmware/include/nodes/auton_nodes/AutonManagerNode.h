#pragma once

#include "lib-rr/nodes/NodeManager.h"
#include "lib-rr/auton/auton_routines/TestPathAuton.h"
#include "lib-rr/auton/auton_routines/TestPoseAuton.h"
#include "lib-rr/auton/auton_routines/TestTurnAuton.h"
#include "auton/auton_routines/BasicAuton.h"
#include "auton/auton_routines/odomTest.h"
#include "lib-rr/pathing/PathManager.h"

class AutonManagerNode : public Node {
private:
    IDriveNode* m_drive_node;
    OdometryNode* m_odom_node;
    InertialSensorNode* m_inertial_sensor_node;

    Auton* m_test_path_auton;
    Auton* m_prog_skills;
    Auton* m_test_auton;

public:
    AutonManagerNode(NodeManager* node_manager, IDriveNode* drive_node, OdometryNode* odom_node, InertialSensorNode* inertial_sensor_node);

    Auton* selected_auton;

    void initialize();

    void autonPeriodic();
};
