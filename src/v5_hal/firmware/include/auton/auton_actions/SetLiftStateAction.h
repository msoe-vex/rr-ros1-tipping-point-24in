#pragma once

#include "api.h"
#include "lib-rr/auton/Auton.h"
#include "nodes/LiftNode.h"

class SetLiftStateAction : public AutonAction {
private:
    LiftNode* m_lift_node;
    LiftNode::LiftState m_state;

public:
    SetLiftStateAction(LiftNode* lift_node, LiftNode::LiftState state);

    void ActionInit();

    actionStatus Action();

    void ActionEnd();
};