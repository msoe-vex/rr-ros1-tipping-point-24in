#include "auton/auton_actions/SetHighRungLiftStateAction.h"

SetHighRungLiftStateAction::SetHighRungLiftStateAction(HighRungLiftNode* lift_node, HighRungLiftNode::HighRungLiftState state) : 
        m_lift_node(lift_node), 
        m_state(state) {
    
}

void SetHighRungLiftStateAction::ActionInit() {

}

AutonAction::actionStatus SetHighRungLiftStateAction::Action() {
    m_lift_node->setLiftState(m_state);
    return END;
}

void SetHighRungLiftStateAction::ActionEnd() {
    
}