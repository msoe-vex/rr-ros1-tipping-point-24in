#include "auton/auton_actions/SetGoalRotatorPosition.h"

SetGoalRotatorPosition::SetGoalRotatorPosition(GoalSpinnerNode* goalSpinner, int position) : 
        m_goalSpinner(goalSpinner), 
        m_position(position)  {
    
}

void SetGoalRotatorPosition::ActionInit() {

}

AutonAction::actionStatus SetGoalRotatorPosition::Action() {
    m_goalSpinner->setSpinnerPosition(m_position);
    return END;
}

void SetGoalRotatorPosition::ActionEnd() {
    
}