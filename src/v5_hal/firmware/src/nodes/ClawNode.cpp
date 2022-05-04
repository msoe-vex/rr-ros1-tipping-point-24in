#include "nodes/ClawNode.h"

ClawNode::ClawNode(NodeManager* node_manager, std::string handle_name, ControllerNode* controller, 
			ADIDigitalOutNode* claw, pros::controller_digital_e_t button1) : 
		IClawNode(node_manager, handle_name), 
		m_controller(controller),
		m_claw(claw),
		m_button1(button1),
		m_claw_open(false),
		m_a_previous_state(false) {
	m_isToggle = true;
}

ClawNode::ClawNode(NodeManager* node_manager, std::string handle_name, ControllerNode* controller, 
			ADIDigitalOutNode* claw, pros::controller_digital_e_t button1, pros::controller_digital_e_t button2) : 
		IClawNode(node_manager, handle_name), 
		m_controller(controller),
		m_claw(claw),
		m_button1(button1),
		m_button2(button2),
		m_claw_open(false),
		m_a_previous_state(false) {
	m_isToggle = false;
}

void ClawNode::initialize() {

}

void ClawNode::useClaw(bool opened) {
	if (opened) {
		m_claw->setValue(0);
	} else {
        m_claw->setValue(1);
	}
}

void ClawNode::setDisabled(bool disabled) {
	m_disabled = disabled;
}

void ClawNode::teleopPeriodic() {
	if (!m_disabled) {
		if (m_isToggle) {
			bool a_current_state = m_controller->getController()->get_digital(m_button1);

		if (a_current_state == 1 && m_a_previous_state == 0) {
				m_claw_open = !m_claw_open;
				useClaw(m_claw_open);
			}

		m_a_previous_state = a_current_state;
	} else {
		if (m_controller->getController()->get_digital(m_button1) == 1) {
			useClaw(true);
		}

			if (m_controller->getController()->get_digital(m_button2) == 1) {
				useClaw(false);
			}
		}
	}
}

void ClawNode::autonPeriodic() {

}

ClawNode::~ClawNode() {

}