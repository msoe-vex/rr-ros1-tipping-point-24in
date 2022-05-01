#include "nodes/IntakeNode.h"

IntakeNode::IntakeNode(NodeManager* node_manager, std::string handle_name, ControllerNode* controller, 
        MotorNode* intake_motor, pros::controller_digital_e_t in_button, bool toggle) : IRollerIntakeNode(node_manager, handle_name), 
        m_controller(controller->getController()),
        m_intake_motor(intake_motor),
        m_in_button(in_button),
        m_toggle(toggle) {
    m_handle_name = handle_name.insert(0, "robot/");
    m_canReverse = false;
}

IntakeNode::IntakeNode(NodeManager* node_manager, std::string handle_name, ControllerNode* controller, 
        MotorNode* intake_motor, pros::controller_digital_e_t in_button, pros::controller_digital_e_t out_button) : IRollerIntakeNode(node_manager, handle_name), 
        m_controller(controller->getController()),
        m_intake_motor(intake_motor),
        m_in_button(in_button),
        m_out_button(out_button) {
    m_handle_name = handle_name.insert(0, "robot/");
    m_canReverse = true;
}

IntakeNode::IntakeNode(NodeManager* node_manager, std::string handle_name, ControllerNode* controller, 
        MotorNode* intake_motor, MotorNode* intake_motor2, pros::controller_digital_e_t in_button, pros::controller_digital_e_t out_button) : IRollerIntakeNode(node_manager, handle_name), 
        m_controller(controller->getController()),
        m_intake_motor(intake_motor),
        m_intake_motor2(intake_motor2),
        m_in_button(in_button),
        m_out_button(out_button) {
    m_handle_name = handle_name.insert(0, "robot/");
    m_canReverse = true;
    m_twoMotors = true;
}

void IntakeNode::setIntakeVoltage(int voltage) {
    m_intake_motor->moveVoltage(voltage);
    if (m_twoMotors) {
        m_intake_motor2->moveVoltage(voltage);
    }
}

void IntakeNode::setIntakeVelocity(float velocity) {
    m_intake_motor->moveVelocity(velocity);
    if (m_twoMotors) {
        m_intake_motor2->moveVelocity(velocity);
    }
}

void IntakeNode::initialize() {

}

void IntakeNode::teleopPeriodic() {
    if (m_toggle) {
        bool upButtonCurrentState = m_controller->get_digital(m_in_button);

        if (upButtonCurrentState == 1 && m_inButtonPreivousState == 0) {
            m_running = !m_running;
        }

        if (m_running) {
            setIntakeVoltage(MAX_MOTOR_VOLTAGE);
        } else {
            setIntakeVoltage(0);
        }

        m_inButtonPreivousState = upButtonCurrentState;
    } else {
        if (m_controller->get_digital(m_in_button)) { 
            setIntakeVoltage(MAX_MOTOR_VOLTAGE);
        } else if (m_canReverse && m_controller->get_digital(m_out_button)) {
            setIntakeVoltage(-1 * MAX_MOTOR_VOLTAGE);
        } else {
            setIntakeVoltage(0);
        }
    }
}

void IntakeNode::autonPeriodic() {
    
}

IntakeNode::~IntakeNode() {
    delete m_intake_motor;
}