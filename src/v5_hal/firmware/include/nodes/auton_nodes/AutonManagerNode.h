#pragma once

#include "lib-rr/nodes/NodeManager.h"
#include "lib-rr/auton/auton_routines/TestPathAuton.h"
#include "lib-rr/auton/auton_routines/TestPoseAuton.h"
#include "lib-rr/auton/auton_routines/TestTurnAuton.h"
#include "auton/auton_routines/MatchAuton.h"
#include "auton/auton_routines/BasicAuton.h"
#include "auton/auton_routines/ProgrammingSkillzAuton.h"
#include "lib-rr/pathing/PathManager.h"

class AutonManagerNode : public Node {
private:
    IDriveNode* m_driveNode;
    OdometryNode* m_odomNode;
    IRollerIntakeNode* m_intakeNode;
    IRollerIntakeNode* m_conveyorNode;
    IRollerIntakeNode* m_flapConveyorNode;
    IClawNode* m_frontClawNode;
    BackClawNode* m_backClaw;
    IClawNode* m_wingArms;
    IClawNode* m_buddyClimb;
    LiftNode* m_liftNode;
    HighRungLiftNode* m_highRungLiftNode;

    Auton* m_test_path_auton;
    Auton* m_prog_skills;
    Auton* m_match_auton;

public:
    AutonManagerNode(NodeManager* nodeManager, IDriveNode* driveNode, OdometryNode* odomNode, IRollerIntakeNode* intakeNode, IRollerIntakeNode* conveyorNode, IRollerIntakeNode* flapConveyorNode, IClawNode* frontClawNode, BackClawNode* backClaw, IClawNode* wingArms, IClawNode* buddyClimb, LiftNode* liftNode, HighRungLiftNode* highRungLiftNode);

    Auton* selected_auton;

    void initialize();

    void autonPeriodic();
};
