#pragma once

#include "lib-rr/nodes/NodeManager.h"
#include "lib-rr/auton/auton_routines/TestPathAuton.h"
#include "lib-rr/auton/auton_routines/TestPoseAuton.h"
#include "lib-rr/auton/auton_routines/TestTurnAuton.h"
#include "auton/auton_routines/MatchAuton.h"
#include "auton/auton_routines/MatchAuton2.h"
#include "auton/auton_routines/BasicAuton.h"
#include "lib-rr/pathing/PathManager.h"
#include "nodes/LiftNode.h"

class AutonManagerNode : public Node {
private:
    IDriveNode* m_driveNode;
    OdometryNode* m_odomNode;
    IClawNode* m_frontClawNode;
    LiftNode* m_liftNode;
    HighRungLiftNode* m_high_rung_lift_node;

    Auton* m_test_path_auton;
    Auton* m_prog_skills;
    Auton* m_match_auton;
    Auton* m_match_auton2;

public:
    AutonManagerNode(NodeManager* node_manager, OdometryNode* odom_node,
        IDriveNode* drive_node, IClawNode* front_claw_node, LiftNode* liftNode,
        HighRungLiftNode* high_rung_lift_node);

    Auton* selected_auton;

    void initialize();

    void autonPeriodic();
};
