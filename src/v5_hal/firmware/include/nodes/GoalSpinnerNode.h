#pragma once

#include "lib-rr/nodes/NodeManager.h"
#include "lib-rr/nodes/subsystems/ILiftNode.h"
#include "lib-rr/nodes/sensor_nodes/ControllerNode.h"
#include "lib-rr/nodes/actuator_nodes/MotorNode.h"
#include "lib-rr/nodes/sensor_nodes/ADIDigitalInNode.h"
#include "lib-rr/nodes/sensor_nodes/ADIAnalogInNode.h"
#include "pros/misc.h"
#include "lib-rr/util/PID.h"

class GoalSpinnerNode : public Node {
public:
    enum SpinnerState {
        SPIN_STRAIGHT, SPIN_180, HOLDING, FREE_MOVING
    };

    GoalSpinnerNode(NodeManager* node_manager, std::string handle_name, 
        ControllerNode* controller, pros::controller_digital_e_t leftSpinButton, 
        pros::controller_digital_e_t rightSpinButton, MotorNode* motor);
    
    void initialize();

    void setSpinnerVoltage(int voltage);

    void setSpinnerVelocity(float velocity);

    void setSpinnerPosition(int position, int tolerance = 5);
    
    void setSpinnerState(SpinnerState state);

    int getPosition();

    void teleopPeriodic();

    void autonPeriodic();

    ~GoalSpinnerNode();

private:    
    // void m_updateSpinnerStateTeleop();

    // void m_goToClosestState();
    
    void m_setSpinnerPID();

    ControllerNode* m_controller;
    MotorNode* m_motor;
    SpinnerState m_state;
    pros::controller_digital_e_t m_leftSpinButton; 
    pros::controller_digital_e_t m_rightSpinButton;

    PID m_pid;

    bool m_leftSpinButtonPreivousState = false;
    bool m_rightSpinButtonPreviousState = false;

    int m_spinStraight = 1000;
    int m_spin180 = 2600;

    int m_target_position;
    int m_tolerance;
};