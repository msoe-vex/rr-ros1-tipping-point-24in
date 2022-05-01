#pragma once

#include "api.h"
#include "lib-rr/auton/Auton.h"
#include "nodes/HighRungLiftNode.h"

class SetHighRungLiftStateAction : public AutonAction {
private:
    HighRungLiftNode* m_lift_node;
    HighRungLiftNode::HighRungLiftState m_state;

public:
    SetHighRungLiftStateAction(HighRungLiftNode* lift_node, HighRungLiftNode::HighRungLiftState state);

    void ActionInit();

    actionStatus Action();

    void ActionEnd();
};