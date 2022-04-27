#include "auton/auton_actions/SetLiftStateAction.h"

SetLiftStateAction::SetLiftStateAction(LiftNode* lift_node, LiftNode::LiftState state) : 
        m_lift_node(lift_node), 
        m_state(state) {
    
}

void SetLiftStateAction::ActionInit() {

}

AutonAction::actionStatus SetLiftStateAction::Action() {
    m_lift_node->setLiftState(m_state);
    return END;
}

void SetLiftStateAction::ActionEnd() {
    
}