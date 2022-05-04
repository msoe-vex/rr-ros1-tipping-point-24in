#pragma once

#include "api.h"
#include "lib-rr/auton/Auton.h"
#include "lib-rr/util/Timer.h"
#include "lib-rr/util/Constants.h"
#include "nodes/GoalSpinnerNode.h"

class SetGoalRotatorPosition : public AutonAction {
private:
    GoalSpinnerNode* m_goalSpinner;
    int m_position;

public:
    SetGoalRotatorPosition(GoalSpinnerNode* goalSpinner, int position);

    void ActionInit();

    actionStatus Action();

    void ActionEnd();
};