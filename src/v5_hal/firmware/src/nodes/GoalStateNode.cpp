#include "nodes/GoalStateNode.h"

GoalStateNode::GoalStateNode(NodeManager* node_manager, std::string handle_name,
        ControllerNode* controller, GoalSpinnerNode* goalSpinner, 
        IClawNode* frontClaw, LiftNode* lift, HighRungLiftNode* highRungLift,
        pros::controller_digital_e_t endgameToggleButton) : Node(node_manager, 5),
        m_controller(controller->getController()),
        m_goalSpinner(goalSpinner),
        m_frontClaw(frontClaw),
        m_lift(lift),
        m_highRungLift(highRungLift),
        m_endgameToggleButton(endgameToggleButton),
        m_state(FREE_MOVING) {
    m_handle_name = handle_name.insert(0, "robot/");
}


void GoalStateNode::initialize() {
    // m_state = STARTING;
}

void GoalStateNode::setState(GoalState state) {
    m_previousState = m_state;
    m_state = state;
    m_stateChange = true;
}

void GoalStateNode::teleopPeriodic() {
    m_updateStateTeleOp();

    int position = m_highRungLift->getPosition();
    if (m_lowPosition < position && position < m_highPosition) {
        m_frontClaw->useClaw(true);
        m_frontClaw->setDisabled(true);
        pros::lcd::print(4, "disable");
    } else {
        m_frontClaw->setDisabled(false);
        pros::lcd::print(4, "enable");
    }

    
    // gets controller input and scales it to [-1, 1]
    double controllerInput = m_controller->get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) / 127.0;

    // setLiftVoltage(max(controllerInput * MAX_MOTOR_VOLTAGE, 0));

    if (m_frontClaw->claw_open) {
        int currentPosition = m_highRungLift->getPosition();
        if (currentPosition < m_highPosition && 
                currentPosition > m_lowPosition) {
            m_highRungLift->setLiftVoltage(max(controllerInput * MAX_MOTOR_VOLTAGE, 0));
        } else if (currentPosition > m_lowPosition &&
                currentPosition < m_highPosition) {
            m_highRungLift->setLiftVoltage(min(controllerInput * MAX_MOTOR_VOLTAGE, 0));
        } else {
            m_highRungLift->setLiftVoltage(controllerInput * MAX_MOTOR_VOLTAGE);
        }
    }

    switch (m_state) {
    
    case FOLLOW_LIFT:
        // HighRungLift follows Lift
        // m_highRungLiftFollowsLift();
        // // all other nodes have free movement
        // m_goalSpinner->setSpinnerState(GoalSpinnerNode::SpinnerState::FREE_MOVING);
        // m_frontClaw->setDisabled(false);
    break;

    case FREE_MOVING: {
        // Free movement of HighRungLift
        // Change state of claw and spinner based on HighRungLift position

        // if lift is within a certain value range
        // int position = m_highRungLift->getPosition();
        // if (m_lowPosition < position && position < m_highPosition) {
        //     m_frontClaw->useClaw(false);
        //     m_frontClaw->setDisabled(true);
        //     pros::lcd::print(4, "disable");
        // } else {
        //     m_frontClaw->setDisabled(false);
        //     pros::lcd::print(4, "enable");
        // }
        // make sure the claw is up
    }
    break;

    default:
        // don't know yet
    break;
    }
}

void GoalStateNode::autonPeriodic() {
    switch (m_state) {
    case STARTING:
        // HighRungNode in loading
        // all other nodes in free movement
    break;

    case FOLLOW_LIFT:
        // same as tele-op
    break;

    case LOADING:
        // HighRungLift to loading position
        // Change state of claw and spinner based on HighRungLift position
    break;

    case STRAIGHT_UP:
        // HighRungLift to straight up position
        // Change state of claw and spinner based on HighRungLift position
    break;

    case SCORING:
        // HighRungLift to scoring up position
        // Change state of claw and spinner based on HighRungLift position
    break;

    default:
    
    break;
    }
}

// these ones and zeros need to be tested
// I am assuming that 1 is piston retracted 
// void GoalStateNode::periodic() {
//     switch (m_state)
//     {
//         case PIVOT_BACK:
//             m_claw->setValue(1);

//             if (m_previousState == PIVOT_DOWN_CLAW_CLOSED) {
//                 m_pivot->setValue(1);
//             } else if (m_stateChange && m_previousState == PIVOT_DOWN_CLAW_OPEN) {
//                 m_timer.Start();
//             } else if (m_timer.Get() > 0.3) {
//                 m_pivot->setValue(1);
//             }        
            
//         break;

//         case PIVOT_DOWN_CLAW_OPEN:
//             m_pivot->setValue(0);

//             if (m_previousState == PIVOT_DOWN_CLAW_CLOSED) {
//                 m_claw->setValue(0);    
//             } else if (m_stateChange && m_previousState == PIVOT_BACK) {
//                 m_timer.Start();
//             } else if (m_timer.Get() > 0.7) {
//                 m_claw->setValue(0);    
//             }       
//         break;

//         case PIVOT_DOWN_CLAW_CLOSED:
//             m_pivot->setValue(0);
//             m_claw->setValue(1);
//         break;
        
//         default:
//             break;
//     }

//     m_stateChange = false;
// }

void GoalStateNode::m_updateStateTeleOp() {
//     // this logic is the exact same as ClawNode I wonder 
//     // how we could combine the two
//     bool endgameToggleButtonnCurrentState = m_controller->get_digital(m_endgameToggleButton);
//     // bool clawButtonCurrentState = m_controller->get_digital(m_clawButton);

//     // there feels like there is a better way to do the state logic when a button is pressed
// 	if (endgameToggleButtonnCurrentState == 1 && m_endgameToggleButtonnPreivousState == 0) {
//         m_endgameMode = !m_endgameMode;
//     }

//     if (m_endgameMode) {
//         m_state = FREE_MOVING;
//     } else {
//         m_state = FOLLOW_LIFT;
//     }

//     // if (clawButtonCurrentState == 1 && m_clawButtonPreviousState == 0) {
//     //     // claw button has been pressed
//     //     // if the claw is pivotted back, pivot it forward and open the claw
//     //     // if not, toggle the position of the claw
//     //     toggleClaw();
//     // }

// 	m_endgameToggleButtonnPreivousState = endgameToggleButtonnCurrentState;
//     // m_clawButtonPreviousState = clawButtonCurrentState;
}

void GoalStateNode::m_highRungLiftFollowsLift() {
    int liftPosition = m_lift->getPosition();

    //formula to translate Lift position to HighRungLiftPosition
    int highRungLiftTargetPosition = liftPosition * m_slope + m_intercept;

    m_highRungLift->setLiftPosition(highRungLiftTargetPosition);
}

GoalStateNode::~GoalStateNode() {

}
