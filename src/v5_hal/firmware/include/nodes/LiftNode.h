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
private:
    ControllerNode* m_controller;
    MotorNode* m_left_motor;
    MotorNode* m_right_motor;
    pros::controller_digital_e_t m_up_button;
    pros::controller_digital_e_t m_down_button;

    PID m_lift_pid;

public:
    LiftNode(NodeManager* node_manager, std::string handle_name, 
        ControllerNode* controller, MotorNode* left_motor, MotorNode* right_motor,
        pros::controller_digital_e_t up_button, pros::controller_digital_e_t down_button);
    
    void initialize();

    void setLiftVoltage(int voltage);

    void setLiftVelocity(int velocity);

    void setLiftPosition(int position);

    int getPosition();

    void teleopPeriodic();

    void autonPeriodic();

    ~LiftNode();
};