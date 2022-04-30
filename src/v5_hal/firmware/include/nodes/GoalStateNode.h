#pragma once

#include "lib-rr/nodes/NodeManager.h"
#include "lib-rr/nodes/sensor_nodes/ControllerNode.h"
#include "lib-rr/nodes/actuator_nodes/ADIDigitalOutNode.h"
#include "lib-rr/util/Timer.h"
#include "nodes/ClawNode.h"
#include "nodes/LiftNode.h"
#include "nodes/HighRungLiftNode.h"
#include "pros/misc.h"

class GoalStateNode : public Node {
public:
    enum GoalStates {
        PIVOT_BACK, PIVOT_DOWN_CLAW_OPEN, PIVOT_DOWN_CLAW_CLOSED
    };

    GoalStateNode(NodeManager* node_manager, std::string handle_name,
        ControllerNode* controller, pros::controller_digital_e_t pivotButton, 
        pros::controller_digital_e_t clawButton, ADIDigitalOutNode* pivot,
        ADIDigitalOutNode* claw);

    void initialize();

    void setState(GoalStates state);

    void togglePivot();

    void toggleClaw();

    void teleopPeriodic();
    
    void autonPeriodic();

    ~GoalStateNode();

private:
    BackClawState m_state;
    BackClawState m_previousState;
    Timer m_timer;

    pros::Controller* m_controller;
    pros::controller_digital_e_t m_pivotButton;
    pros::controller_digital_e_t m_clawButton;
    ADIDigitalOutNode* m_pivot;
    ADIDigitalOutNode* m_claw;

    std::string m_handle_name;

    bool m_pivotButtonPreivousState = false;
    bool m_clawButtonPreviousState = false;
    bool m_stateChange = false;

    void periodic();
};
