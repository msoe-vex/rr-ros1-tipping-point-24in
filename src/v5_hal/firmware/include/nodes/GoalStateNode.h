#pragma once

#include "lib-rr/nodes/NodeManager.h"
#include "lib-rr/nodes/sensor_nodes/ControllerNode.h"
#include "lib-rr/nodes/actuator_nodes/ADIDigitalOutNode.h"
#include "lib-rr/util/Timer.h"
#include "nodes/ClawNode.h"
#include "nodes/LiftNode.h"
#include "nodes/HighRungLiftNode.h"
#include "nodes/GoalSpinnerNode.h"
#include "pros/misc.h"

class GoalStateNode : public Node {
public:
    enum GoalState {
        STARTING, FOLLOW_LIFT, FREE_MOVING, LOADING, STRAIGHT_UP, SCORING
    };

    GoalStateNode(NodeManager* node_manager, std::string handle_name,
        ControllerNode* controller, GoalSpinnerNode* goalSpinner, 
        IClawNode* frontClaw, LiftNode* lift, HighRungLiftNode* highRungLift,
        pros::controller_digital_e_t endgameToggleButton);

    void initialize();

    void setState(GoalState state);

    void teleopPeriodic();
    
    void autonPeriodic();

    ~GoalStateNode();

private:
    void m_updateStateTeleOp();

    void m_highRungLiftFollowsLift();

    GoalState m_state;
    GoalState m_previousState;
    Timer m_timer;

    pros::Controller* m_controller;
    GoalSpinnerNode* m_goalSpinner;
    IClawNode* m_frontClaw;
    LiftNode* m_lift;
    HighRungLiftNode* m_highRungLift;
    pros::controller_digital_e_t m_endgameToggleButton

    std::string m_handle_name;

    bool m_endgameToggleButtonnPreivousState = false;
    bool m_clawButtonPreviousState = false;
    bool m_endgameMode = false;
    bool m_stateChange = false;

    // HighRungLift to Lift function
    float m_slope = -55.0; // NEEDS TO BE CHANGED
    float m_intercept = 15.0; // NEEDS TO BE CHANGED

    void periodic();
};
