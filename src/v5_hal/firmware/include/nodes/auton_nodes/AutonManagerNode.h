#pragma once

#include "lib-rr/nodes/NodeManager.h"
#include "lib-rr/auton/auton_routines/TestPathAuton.h"
#include "lib-rr/auton/auton_routines/TestPoseAuton.h"
#include "lib-rr/auton/auton_routines/TestTurnAuton.h"
#include "auton/auton_routines/MatchAuton.h"
#include "auton/auton_routines/LeftAuton.h"
#include "auton/auton_routines/BasicAuton.h"
#include "lib-rr/pathing/PathManager.h"
#include "nodes/LiftNode.h"
#include "nodes/BackClawNode.h"

class AutonManagerNode : public Node {
private:
    IDriveNode* m_driveNode;
    OdometryNode* m_odomNode;
    IClawNode* m_frontClawNode;
    LiftNode* m_liftNode;
    HighRungLiftNode* m_highRungLiftNode;
    BackClawNode* m_backClawNode;
    IRollerIntakeNode* m_intakeNode;
    IRollerIntakeNode* m_conveyorNode;
    IRollerIntakeNode* m_flapConveyorNode;

    Auton* m_test_path_auton;
    Auton* m_prog_skills;
    Auton* m_match_auton;
    Auton* m_leftAuton;
    
    std::string pathJSON;

public:
    AutonManagerNode(NodeManager* node_manager, OdometryNode* odom_node,
        IDriveNode* drive_node, IClawNode* front_claw_node, LiftNode* liftNode,
        HighRungLiftNode* high_rung_lift_node, BackClawNode* backClawNode,
        IRollerIntakeNode* intakeNode, IRollerIntakeNode* conveyorNode, 
        IRollerIntakeNode* flapConveyorNode);

    Auton* selected_auton;
    std::vector<Auton*> autons;

    void initialize();
    
    void setPathsFile(std::string);

    void autonPeriodic();
};
