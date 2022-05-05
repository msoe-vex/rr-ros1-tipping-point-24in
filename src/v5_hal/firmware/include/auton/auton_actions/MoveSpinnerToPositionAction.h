#pragma once

#include "api.h"
#include "lib-rr/auton/Auton.h"
#include "nodes/GoalSpinnerNode.h"

class MoveSpinnerToPositionAction : public AutonAction {
private:
    GoalSpinnerNode* m_goalSpinner;
    int m_position;
    int m_tolerance;
    bool m_waitForCompletion;

public:
    MoveSpinnerToPositionAction(GoalSpinnerNode* goalSpinner, int position, int tolerance=20, bool waitForCompletion=false);

    void ActionInit();

    actionStatus Action();

    void ActionEnd();
};