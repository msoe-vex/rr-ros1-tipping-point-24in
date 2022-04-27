#pragma once

#include "lib-rr/nodes/NodeManager.h"
#include "lib-rr/auton/auton_routines/TestPathAuton.h"
#include "lib-rr/auton/auton_routines/TestPoseAuton.h"
#include "lib-rr/auton/auton_routines/TestTurnAuton.h"
#include "auton/auton_routines/MatchAuton.h"
#include "lib-rr/pathing/PathManager.h"

class AutonManagerNode : public Node {
private:
    IDriveNode* m_driveNode;
    OdometryNode* m_odomNode;
    IClawNode* m_frontClawNode;

    Auton* m_test_path_auton;
    Auton* m_prog_skills;
    Auton* m_match_auton;

public:
    AutonManagerNode(NodeManager* node_manager, OdometryNode* odom_node, IDriveNode* drive_node, IClawNode* front_claw_node);

    Auton* selected_auton;

    void initialize();

    void autonPeriodic();
};
