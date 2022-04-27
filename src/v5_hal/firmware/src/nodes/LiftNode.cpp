#include "nodes/LiftNode.h"

LiftNode::LiftNode(NodeManager* node_manager, std::string handle_name, 
        ControllerNode* controller, MotorNode* left_motor, 
        MotorNode* right_motor, ADIDigitalInNode* bottom_limit_switch, 
        ADIDigitalInNode* top_limit_switch, ADIAnalogInNode* potentiometer) : 
        ILiftNode(node_manager, handle_name), 
        m_controller(controller),
        m_left_motor(left_motor),
        m_right_motor(right_motor),
        m_bottom_limit_switch(bottom_limit_switch),
        m_top_limit_switch(top_limit_switch),
        m_potentiometer(potentiometer),
        m_lift_state(HOLDING),
        m_lift_pid(0.002, 0., 0., 0), 
        m_target_position(0),
        m_tolerance(10) {

}

void LiftNode::initialize() {
    m_left_motor->getMotor()->set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	m_right_motor->getMotor()->set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    
    // needs to be changed when going back to potentiometer
    m_left_motor->getMotor()->set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);

    // TESTING CODE
    pros::lcd::initialize();
};

void LiftNode::setLiftVoltage(int voltage) {
    if (m_top_limit_switch->getValue() == 1) {
        m_left_motor->moveVoltage(min(voltage, 0));
        m_right_motor->moveVoltage(min(voltage, 0));
    } else {
        m_left_motor->moveVoltage(voltage);
        m_right_motor->moveVoltage(voltage);
    }
};

void LiftNode::setLiftVelocity(float velocity) {
    if (m_top_limit_switch->getValue() == 1) {
        m_left_motor->moveVelocity(min(velocity, 0.f));
        m_right_motor->moveVelocity(min(velocity, 0.f));
    } else {
        m_left_motor->moveVelocity(velocity);
        m_right_motor->moveVelocity(velocity);
    }
};

void LiftNode::setLiftPosition(int position, int tolerance) {
    m_target_position = position;
    m_tolerance = tolerance;
};

int LiftNode::getPosition() { // change back to use pot
    return m_left_motor->getPosition();
}

void LiftNode::updateLiftState() {
    int positionBoundUpper = getPosition() + m_tolerance;
    int positionBoundLower = getPosition() - m_tolerance;
    if(positionBoundLower < m_target_position && m_target_position < positionBoundUpper) {
        m_lift_state = HOLDING;
    } else {
        m_lift_state = UPDATING;
    }
}

void LiftNode::teleopPeriodic() {
    if (m_controller->getController()->get_digital(pros::E_CONTROLLER_DIGITAL_R1) && 
        !m_controller->getController()->get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        setLiftVoltage(MAX_MOTOR_VOLTAGE); // using voltage here cause we don't know max motor velocity for sure
    } else if (m_controller->getController()->get_digital(pros::E_CONTROLLER_DIGITAL_R2) && 
        !m_controller->getController()->get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        setLiftVoltage(-MAX_MOTOR_VOLTAGE);
    } else {
        setLiftVelocity(0);
    }
};

void LiftNode::autonPeriodic() {
    updateLiftState();
    
    switch (m_lift_state) {
        case UPDATING:
            m_setLiftPID();
        break;
        case HOLDING:
            setLiftVelocity(0);
        break;
    }
};

void LiftNode::m_setLiftPID() {
    int errorPosition = m_target_position - getPosition();
    float lift_feedback = m_lift_pid.calculate(errorPosition);
    // pros::lcd::print(0, "errorPosition: %f\n", errorPosition);
    // pros::lcd::print(1, "lift_feedback: %f\n", lift_feedback);
    setLiftVelocity(lift_feedback * MAX_VELOCITY);
}

LiftNode::~LiftNode() {

}