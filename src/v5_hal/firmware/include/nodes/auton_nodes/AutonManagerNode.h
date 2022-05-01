#pragma once

#include "lib-rr/nodes/NodeManager.h"
#include "lib-rr/auton/auton_routines/TestPathAuton.h"
#include "lib-rr/auton/auton_routines/TestPoseAuton.h"
#include "lib-rr/auton/auton_routines/TestTurnAuton.h"
#include "lib-rr/nodes/subsystems/IRollerIntakeNode.h"
#include "auton/auton_routines/MatchAuton.h"
#include "auton/auton_routines/BasicAuton.h"
#include "auton/auton_routines/ProgrammingSkillzAuton.h"
#include "lib-rr/pathing/PathManager.h"
#include "nodes/HighRungLiftNode.h"
#include "nodes/BackClawNode.h"
#include "nodes/LiftNode.h"

class AutonManagerNode : public Node {
private:
    IDriveNode* m_driveNode;
    OdometryNode* m_odomNode;
    IClawNode* m_frontClawNode;
    HighRungLiftNode* m_highRungLiftNode;
    IRollerIntakeNode* m_intakeNode;
    IRollerIntakeNode* m_conveyorNode;
    IRollerIntakeNode* m_flapConveyorNode;
    BackClawNode* m_backClaw;
    IClawNode* m_buddyClimb;
    LiftNode* m_liftNode;

    Auton* m_test_path_auton;
    Auton* m_prog_skills;
    Auton* m_match_auton;

public:
    AutonManagerNode(NodeManager* node_manager, OdometryNode* odomNode, 
        IDriveNode* driveNode, IClawNode* frontClawNode, HighRungLiftNode* highRungLiftNode,
        IRollerIntakeNode* intakeNode, IRollerIntakeNode* conveyorNode, IRollerIntakeNode* flapConveyorNode, 
        BackClawNode* backClaw, IClawNode* buddyClimb, LiftNode* liftNode);

    Auton* selected_auton;

    void initialize();

    void autonPeriodic();
};
