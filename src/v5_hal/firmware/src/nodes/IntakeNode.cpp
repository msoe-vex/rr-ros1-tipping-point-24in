#include "nodes/IntakeNode.h"

IntakeNode::IntakeNode(NodeManager* node_manager, std::string handle_name, ControllerNode* controller, 
        MotorNode* intake_motor) : Node(node_manager, 10), 
        m_controller(controller->getController()),
        m_intake_motor(intake_motor) {
    m_handle_name = handle_name.insert(0, "robot/");
}

void IntakeNode::setIntakeVoltage(int voltage) {
    m_intake_motor->moveVoltage(voltage);
}

void IntakeNode::initialize() {

}

void IntakeNode::teleopPeriodic() {
    if (m_controller->get_digital(pros::E_CONTROLLER_DIGITAL_R1)) { 
        setIntakeVoltage(MAX_MOTOR_VOLTAGE);
    } else if (m_controller->get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        setIntakeVoltage(-1 * MAX_MOTOR_VOLTAGE);
    } else {
        setIntakeVoltage(0);
    }
}

void IntakeNode::autonPeriodic() {
    
}

IntakeNode::~IntakeNode() {
    delete m_intake_motor;
}