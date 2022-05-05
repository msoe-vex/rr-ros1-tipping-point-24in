#include "auton/auton_actions/MoveSpinnerToPositionAction.h"

MoveSpinnerToPositionAction::MoveSpinnerToPositionAction(GoalSpinnerNode* goalSpinner, int position, int tolerance, bool waitForCompletion) : 
        m_goalSpinner(goalSpinner), 
        m_position(position),
        m_tolerance(tolerance),
        m_waitForCompletion(waitForCompletion) {
    
}

void MoveSpinnerToPositionAction::ActionInit() {

}

AutonAction::actionStatus MoveSpinnerToPositionAction::Action() {
    m_goalSpinner->setSpinnerState(GoalSpinnerNode::FREE_MOVING);
    m_goalSpinner->setSpinnerPosition(m_position, m_tolerance);

    if (!m_waitForCompletion) {
        return END;
    } else {
        int currentPos = m_goalSpinner->getPosition();
        int lowerBound = m_position - m_tolerance;
        int upperBound = m_position + m_tolerance;

        if (currentPos < lowerBound || currentPos > upperBound) {
            return CONTINUE;
        } else {
            return END;
        }
    }
    
}

void MoveSpinnerToPositionAction::ActionEnd() {
    
}