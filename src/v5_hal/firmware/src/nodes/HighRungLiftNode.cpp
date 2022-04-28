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
        m_target_position(0),
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
    pros::lcd::print(0, "pot: %d", getPosition());
    
    // gets controller input and scales it to [-1, 1]
    double controllerInput = m_controller->getController()->get_analog(m_joystick) / 127;

    setLiftVoltage(controllerInput * MAX_MOTOR_VOLTAGE);
};

void HighRungLiftNode::autonPeriodic() { 
    switch (m_lift_state) {
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

/**
 * Only called in teleopPeriodic()
 * */
// void HighRungLiftNode::m_updateLiftStateTeleop() { 
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


// void HighRungLiftNode::m_goToClosestState() {
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