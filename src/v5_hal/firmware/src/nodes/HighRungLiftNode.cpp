#include "nodes/HighRungLiftNode.h"

HighRungLiftNode::HighRungLiftNode(NodeManager* node_manager, std::string handle_name, 
        ControllerNode* controller, pros::controller_analog_e_t joystick, 
        MotorNode* motor, ADIAnalogInNode* potentiometer) : 
        ILiftNode(node_manager, handle_name), 
        m_controller(controller),
        m_joystick(joystick),
        m_motor(motor),
        m_potentiometer(potentiometer),
        m_state(FREE_MOVING),
        m_lift_pid(0.002, 0., 0., 0), 
        m_target_position(m_loadingPosition),
        m_tolerance(5) {

}

void HighRungLiftNode::initialize() {
    m_motor->getMotor()->set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    pros::lcd::initialize();
};

void HighRungLiftNode::setLiftVoltage(int voltage) {
    int currentPosition = getPosition();

    if (currentPosition > m_scoringPosition) {
        m_motor->moveVoltage(min(voltage, 0));
    } else if (currentPosition < m_loadingPosition) {
        m_motor->moveVoltage(max(voltage, 0));
    } else {
        m_motor->moveVoltage(voltage);
    }
};

void HighRungLiftNode::setLiftVelocity(float velocity) {
    int currentPosition = getPosition();
    
    if (currentPosition > m_scoringPosition) {
        m_motor->moveVelocity(min(velocity, 0.f));
    } else if (currentPosition < m_loadingPosition) {
        m_motor->moveVelocity(max(velocity, 0.f));
    } else {
        m_motor->moveVelocity(velocity);
    }
};

void HighRungLiftNode::setLiftPosition(int position, int tolerance) {
    m_target_position = position;
    m_tolerance = tolerance;
};

/**
 * This should only be called from autonomous 
 * */
void HighRungLiftNode::setLiftState(HighRungLiftState state) {
    m_state = state;
}

int HighRungLiftNode::getPosition() { // change back to use pot
    return m_potentiometer->getValue();
}

void HighRungLiftNode::teleopPeriodic() {
<<<<<<< HEAD
    // pros::lcd::print(0, "pot: %d", getPosition());
=======
    pros::lcd::print(2, "pot: %d", getPosition());
>>>>>>> main
    
    switch (m_state) {
    
    case FOLLOW_POSITION:
        // outside node updates position
        m_setLiftPID();
    break;
    
    default:
        // gets controller input and scales it to [-1, 1]
        double controllerInput = m_controller->getController()->get_analog(m_joystick) / 127.0;

        setLiftVoltage(controllerInput * MAX_MOTOR_VOLTAGE);
    break;
    }
    
};

void HighRungLiftNode::autonPeriodic() { 
    switch (m_state) {
        case LOADING:
            setLiftPosition(m_loadingPosition);
        break;
        
        case STRAIGHT_UP: 
            setLiftPosition(m_straightUpPosition);
        break;
        
        case SCORING:
            setLiftPosition(m_scoringPosition);
        break;

        default:
            setLiftPosition(m_target_position);
        break;
    }

    m_setLiftPID();
};

void HighRungLiftNode::m_setLiftPID() {
    int errorPosition = m_target_position - getPosition();
    // pros::lcd::print(4, "m_target_position: %d\n", m_target_position);
    float lift_feedback = m_lift_pid.calculate(errorPosition);
    // pros::lcd::print(1, "lift_feedback: %f\n", lift_feedback);
    // pros::lcd::print(0, "encoder: %d\n", getPosition());
    setLiftVelocity(lift_feedback * MAX_VELOCITY);
}

HighRungLiftNode::~HighRungLiftNode() {

}