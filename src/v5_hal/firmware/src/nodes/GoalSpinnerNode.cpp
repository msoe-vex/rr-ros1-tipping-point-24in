#include "nodes/GoalSpinnerNode.h"

GoalSpinnerNode::GoalSpinnerNode(NodeManager* node_manager, std::string handle_name, 
        ControllerNode* controller, pros::controller_digital_e_t leftSpinButton, 
        pros::controller_digital_e_t rightSpinButton, MotorNode* motor) : 
        Node(node_manager, 10), 
        m_controller(controller),
        m_leftSpinButton(leftSpinButton),
        m_rightSpinButton(rightSpinButton),
        m_motor(motor),
        m_state(FREE_MOVING),
        m_pid(0.002, 0., 0., 0), 
        m_target_position(0),
        m_tolerance(5) {

}

void GoalSpinnerNode::initialize() {
    m_motor->getMotor()->set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    
    // needs to be changed when going back to potentiometer
    m_motor->getMotor()->set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);

    // TESTING CODE
    pros::lcd::initialize();
};

void GoalSpinnerNode::setSpinnerVoltage(int voltage) {
    m_motor->moveVoltage(voltage);
};

void GoalSpinnerNode::setSpinnerVelocity(float velocity) {
    m_motor->moveVelocity(velocity);
};

void GoalSpinnerNode::setSpinnerPosition(int position, int tolerance) {
    m_target_position = position;
    m_tolerance = tolerance;
};

/**
 * This should only be called from autonomous 
 * */
void GoalSpinnerNode::setSpinnerState(SpinnerState state) {
    m_state = state;
}

int GoalSpinnerNode::getPosition() { // change back to use pot
    return m_motor->getMotor()->get_position();
}

void GoalSpinnerNode::teleopPeriodic() {
    switch (m_state) {
        case HOLDING:
            setSpinnerPosition(m_target_position);
            // pros::lcd::print(2, "Lift State: DOWN");
            m_setSpinnerPID();
        break;
        
        case FREE_MOVING: 
        
    pros::lcd::print(4, "position: %d\n", getPosition());
            if (m_controller->getController()->get_digital(m_leftSpinButton) && 
                !m_controller->getController()->get_digital(m_rightSpinButton)) {
                setSpinnerVoltage(MAX_MOTOR_VOLTAGE); // using voltage here cause we don't know max motor velocity for sure
            } else if (m_controller->getController()->get_digital(m_rightSpinButton) && 
                !m_controller->getController()->get_digital(m_leftSpinButton)) {
                setSpinnerVoltage(-MAX_MOTOR_VOLTAGE);
            } else {
                setSpinnerVelocity(0);
            }   
            // pros::lcd::print(2, "Lift State: FREE_MOVING");
        break;
        
        // should not be used in tele-op
        case SPIN_180:
            setSpinnerPosition(m_spin180);
            // pros::lcd::print(2, "Lift State: FULLY_UP");
            m_setSpinnerPID();
        break;
        
        // should not be used in tele-op
        case SPIN_STRAIGHT:
            setSpinnerPosition(m_spinStraight);
            // pros::lcd::print(2, "Lift State: FULLY_UP");
            m_setSpinnerPID();
        break;

        default:
            setSpinnerPosition(m_target_position);
            m_setSpinnerPID();
            // pros::lcd::print(2, "Lift State: default");
        break;
    }
};

void GoalSpinnerNode::autonPeriodic() { 
    switch (m_state) {
        case SPIN_180:
            setSpinnerPosition(m_spin180);
            // pros::lcd::print(2, "Lift State: FULLY_UP");
        break;
        
        case SPIN_STRAIGHT:
            setSpinnerPosition(m_spinStraight);
            // pros::lcd::print(2, "Lift State: FULLY_UP");
        break;

        default:
            setSpinnerPosition(m_target_position);
            // pros::lcd::print(2, "Lift State: default");
        break;
    }

    m_setSpinnerPID();
};

/**
 * Only called in teleopPeriodic()
 * */
// void GoalSpinnerNode::m_updateSpinnerStateTeleop() { 
//     bool moveUp = false;
//     bool moveDown = false;
    
//     // this logic is the exact same as ClawNode I wonder 
//     // how we could combine the two
//     bool upButtonCurrentState = m_controller->getController()->get_digital(m_upButton);
//     bool downButtonCurrentState = m_controller->getController()->get_digital(m_downButton);
//     bool freeMoveButtonCurrentState = m_controller->getController()->get_digital(m_freeMoveButton);

// 	if ((upButtonCurrentState == 1 && m_upButtonPreivousState == 0) &&
//             !(downButtonCurrentState == 1 && m_downButtonPreviousState == 0)) {
//         moveUp = true;
//     }

//     if ((downButtonCurrentState == 1 && m_downButtonPreviousState == 0) &&
//             !(upButtonCurrentState == 1 && m_upButtonPreivousState == 0)) {
//         moveDown = true;
//     }

//     if (freeMoveButtonCurrentState == 1 && m_freeMoveButtonPreviousState == 0) {
//         m_freeMoving = !m_freeMoving;
//     }

// 	m_upButtonPreivousState = upButtonCurrentState;
//     m_downButtonPreviousState = downButtonCurrentState;
//     m_freeMoveButtonPreviousState = freeMoveButtonCurrentState;
    
//     switch (m_lift_state) { 
//         case DOWN:
//             if (m_freeMoving) {
//                 m_lift_state = FREE_MOVING;
//             } else if (moveUp) {
//                 m_lift_state = UP_FOR_RINGS;
//             }
//         break;
        
//         case UP_FOR_RINGS:
//             if (m_freeMoving) {
//                 m_lift_state = FREE_MOVING;
//             } else {
//                 if (moveUp) {
//                     m_lift_state = FULLY_UP;
//                 } else if (moveDown) {
//                     m_lift_state = DOWN;
//                 }
//             }
//         break;
        
//         case FULLY_UP:
//             if (m_freeMoving) {
//                 m_lift_state = FREE_MOVING;
//             } else if (moveDown) {
//                 m_lift_state = UP_FOR_RINGS;
//             }
//         break;

//         case FREE_MOVING:
//             if (!m_freeMoving) {
//                 m_goToClosestState();
//             }
//         break;
//     }

//     // pros::lcd::print(3, "m_freeMoving: %d\n", m_freeMoving);

// }


// void GoalSpinnerNode::m_goToClosestState() {
//     int currentPosition = getPosition();
//     int middleOfDownAndUpForRings = (m_upForRingsPosition + m_downPosition) / 2;
//     int middleOfUpForRingsAndFullyUp = (m_fullyUpPosition + m_upForRingsPosition) / 2;
    
//     if (currentPosition <= middleOfDownAndUpForRings) {
//         // the lift is closer to the DOWN position than any other position
//         m_lift_state = DOWN;
//     } else if (middleOfDownAndUpForRings < currentPosition && currentPosition < middleOfUpForRingsAndFullyUp) {
//         // the lift is closer to the UP_FOR_RINGS position than FULLY_UP or DOWN
//         m_lift_state = UP_FOR_RINGS;
//     } else {
//         // the lift is closer to the FULLY_UP position than any other position
//         m_lift_state = FULLY_UP;
//     }
// }

void GoalSpinnerNode::m_setSpinnerPID() {
    int errorPosition = m_target_position - getPosition();
    // pros::lcd::print(4, "m_target_position: %d\n", m_target_position);
    float feedback = m_pid.calculate(errorPosition);
    // pros::lcd::print(1, "lift_feedback: %f\n", lift_feedback);
    pros::lcd::print(4, "position: %d\n", getPosition());
    setSpinnerVelocity(feedback * MAX_VELOCITY);
}

GoalSpinnerNode::~GoalSpinnerNode() {

}