#include "nodes/LiftNode.h"

LiftNode::LiftNode(NodeManager* node_manager, std::string handle_name, 
        ControllerNode* controller, pros::controller_digital_e_t upButton, 
        pros::controller_digital_e_t downButton, pros::controller_digital_e_t freeMoveButton,
         MotorNode* left_motor, MotorNode* right_motor, ADIDigitalInNode* bottom_limit_switch, 
        ADIDigitalInNode* top_limit_switch, ADIAnalogInNode* potentiometer) : 
        ILiftNode(node_manager, handle_name), 
        m_controller(controller),
        m_upButton(upButton),
        m_downButton(downButton),
        m_freeMoveButton(freeMoveButton),
        m_left_motor(left_motor),
        m_right_motor(right_motor),
        m_bottom_limit_switch(bottom_limit_switch),
        m_top_limit_switch(top_limit_switch),
        m_potentiometer(potentiometer),
        m_lift_state(FULLY_UP),
        m_lift_pid(0.002, 0., 0., 0), 
        m_target_position(0),
        m_tolerance(5) {

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
    int currentPosition = getPosition();

    if (m_top_limit_switch->getValue() == 1 || currentPosition > m_fullyUpPosition) {
        m_left_motor->moveVoltage(min(voltage, 0));
        m_right_motor->moveVoltage(min(voltage, 0));
    } else if (currentPosition < m_downPosition) {
        m_left_motor->moveVoltage(max(voltage, 0));
        m_right_motor->moveVoltage(max(voltage, 0));
    } else {
        m_left_motor->moveVoltage(voltage);
        m_right_motor->moveVoltage(voltage);
    }
};

void LiftNode::setLiftVelocity(float velocity) {
    int currentPosition = getPosition();
    
    if (m_top_limit_switch->getValue() == 1 || currentPosition > m_fullyUpPosition) {
        m_left_motor->moveVelocity(min(velocity, 0.f));
        m_right_motor->moveVelocity(min(velocity, 0.f));
    } else if (currentPosition < m_downPosition) {
        m_left_motor->moveVelocity(max(velocity, 0.f));
        m_right_motor->moveVelocity(max(velocity, 0.f));
    } else {
        m_left_motor->moveVelocity(velocity);
        m_right_motor->moveVelocity(velocity);
    }
};

void LiftNode::setLiftPosition(int position, int tolerance) {
    m_target_position = position;
    m_tolerance = tolerance;
};

/**
 * This should only be called from autonomous 
 * */
void LiftNode::setLiftState(LiftState state) {
    m_lift_state = state;
}

int LiftNode::getPosition() { // change back to use pot
    return m_potentiometer->getValue();
}

void LiftNode::teleopPeriodic() {
    m_updateLiftStateTeleop();

    switch (m_lift_state) {
        case DOWN:
            setLiftPosition(m_downPosition);
            pros::lcd::print(2, "Lift State: DOWN");
        break;
        
        case UP_FOR_RINGS: 
            setLiftPosition(m_upForRingsPosition);
            pros::lcd::print(2, "Lift State: UP_FOR_RINGS");
        break;
        
        case FULLY_UP:
            setLiftPosition(m_fullyUpPosition);
            pros::lcd::print(2, "Lift State: FULLY_UP");
        break;
        
        case FREE_MOVING: 
            if (m_controller->getController()->get_digital(m_upButton) && 
                !m_controller->getController()->get_digital(m_downButton)) {
                setLiftVoltage(MAX_MOTOR_VOLTAGE); // using voltage here cause we don't know max motor velocity for sure
            } else if (m_controller->getController()->get_digital(m_downButton) && 
                !m_controller->getController()->get_digital(m_upButton)) {
                setLiftVoltage(-MAX_MOTOR_VOLTAGE);
            } else {
                setLiftPosition(0);
            }   
            pros::lcd::print(2, "Lift State: FREE_MOVING");
        break;

        default:
            setLiftPosition(m_target_position);
            pros::lcd::print(2, "Lift State: default");
        break;
    }

    m_setLiftPID();
};

void LiftNode::autonPeriodic() { 
    switch (m_lift_state) {
        case DOWN:
            setLiftPosition(-4000);
        break;
        
        case UP_FOR_RINGS: 
            setLiftPosition(-3000);
        break;
        
        case FULLY_UP:
            setLiftPosition(0);
        break;

        default:
            setLiftPosition(m_target_position);
        break;
    }

    m_setLiftPID();
};

/**
 * Only called in teleopPeriodic()
 * */
void LiftNode::m_updateLiftStateTeleop() { 
    bool moveUp = false;
    bool moveDown = false;
    bool freeMoving = false;
    
    // this logic is the exact same as ClawNode I wonder 
    // how we could combine the two
    bool upButtonCurrentState = m_controller->getController()->get_digital(m_upButton);
    bool downButtonCurrentState = m_controller->getController()->get_digital(m_downButton);
    bool freeMoveButtonCurrentState = m_controller->getController()->get_digital(m_freeMoveButton);

	if ((upButtonCurrentState == 1 && m_upButtonPreivousState == 0) &&
            !(downButtonCurrentState == 1 && m_downButtonPreviousState == 0)) {
        moveUp = true;
    }

    if ((downButtonCurrentState == 1 && m_downButtonPreviousState == 0) &&
            !(upButtonCurrentState == 1 && m_upButtonPreivousState == 0)) {
        moveDown = true;
    }

    if (freeMoveButtonCurrentState == 1 && m_freeMoveButtonPreviousState == 0) {
        freeMoving = !freeMoving;
    }

	m_upButtonPreivousState = upButtonCurrentState;
    m_downButtonPreviousState = downButtonCurrentState;
    m_freeMoveButtonPreviousState = freeMoveButtonCurrentState;
    
    switch (m_lift_state) { 
        case DOWN:
            if (freeMoving) {
                m_lift_state = FREE_MOVING;
            } else if (moveUp) {
                m_lift_state = UP_FOR_RINGS;
            }
        break;
        
        case UP_FOR_RINGS:
            if (freeMoving) {
                m_lift_state = FREE_MOVING;
            } else {
                if (moveUp) {
                    m_lift_state = FULLY_UP;
                } else if (moveDown) {
                    m_lift_state = DOWN;
                }
            }
        break;
        
        case FULLY_UP:
            if (freeMoving) {
                m_lift_state = FREE_MOVING;
            } else if (moveDown) {
                m_lift_state = UP_FOR_RINGS;
            }
        break;

        case FREE_MOVING:
            if (!freeMoving) {
                m_goToClosestState();
            }
        break;
    }
}

void LiftNode::m_goToClosestState() {
    int currentPosition = getPosition();
    
    if (currentPosition <= -3500) {
        // the lift is closer to the DOWN position than any other position
        m_lift_state = DOWN;
    } else if (-3500 < currentPosition && currentPosition < -1500) {
        // the lift is closer to the UP_FOR_RINGS position than FULLY_UP or DOWN
        m_lift_state = UP_FOR_RINGS;
    } else {
        // the lift is closer to the FULLY_UP position than any other position
        m_lift_state = FULLY_UP;
    }
}

void LiftNode::m_setLiftPID() {
    int errorPosition = m_target_position - getPosition();
    pros::lcd::print(4, "m_target_position: %d\n", m_target_position);
    pros::lcd::print(3, "errorPosition: %d\n", errorPosition);
    float lift_feedback = m_lift_pid.calculate(errorPosition);
    pros::lcd::print(1, "lift_feedback: %f\n", lift_feedback);
    pros::lcd::print(0, "encoder: %d\n", getPosition());
    setLiftVelocity(lift_feedback * MAX_VELOCITY);
}

LiftNode::~LiftNode() {

}