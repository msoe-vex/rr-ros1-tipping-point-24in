#pragma once

#include "lib-rr/nodes/NodeManager.h"
#include "lib-rr/nodes/subsystems/ILiftNode.h"
#include "lib-rr/nodes/sensor_nodes/ControllerNode.h"
#include "lib-rr/nodes/actuator_nodes/MotorNode.h"
#include "lib-rr/nodes/sensor_nodes/ADIDigitalInNode.h"
#include "lib-rr/nodes/sensor_nodes/ADIAnalogInNode.h"
#include "pros/misc.h"
#include "lib-rr/util/PID.h"

class LiftNode : public ILiftNode {
public:
    enum LiftState {
        UPDATING, HOLDING
    };

    LiftNode(NodeManager* node_manager, std::string handle_name, 
        ControllerNode* controller, MotorNode* left_motor, 
        MotorNode* right_motor, ADIDigitalInNode* bottom_limit_switch, 
        ADIDigitalInNode* top_limit_switch, ADIAnalogInNode* potentiometer);
    
    void initialize();

    void setLiftVoltage(int voltage);

    void setLiftVelocity(float velocity);

    void setLiftPosition(int position, int tolerance = 20);

    int getPosition();

    void updateLiftState();

    void teleopPeriodic();

    void autonPeriodic();

    ~LiftNode();

private:    
    void m_setLiftPID();

    ControllerNode* m_controller;
    MotorNode* m_left_motor;
    MotorNode* m_right_motor;
    ADIDigitalInNode* m_bottom_limit_switch;
    ADIDigitalInNode* m_top_limit_switch;
    ADIAnalogInNode* m_potentiometer;
    LiftState m_lift_state;

    PID m_lift_pid;

    int m_target_position;
    int m_tolerance;
};