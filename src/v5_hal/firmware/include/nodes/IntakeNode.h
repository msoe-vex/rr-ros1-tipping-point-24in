#pragma once

#include "lib-rr/nodes/NodeManager.h"
#include "api.h"
#include "lib-rr/nodes/actuator_nodes/MotorNode.h"
#include "lib-rr/nodes/sensor_nodes/ControllerNode.h"
#include "lib-rr/nodes/actuator_nodes/ADIDigitalOutNode.h"
#include "lib-rr/nodes/subsystems/IRollerIntakeNode.h"
#include "lib-rr/util/Constants.h"

class IntakeNode : public IRollerIntakeNode {
private:
    pros::Controller* m_controller;
    MotorNode* m_intake_motor;
    MotorNode* m_intake_motor2;

    bool m_canReverse = false;
    bool m_twoMotors = false;
    pros::controller_digital_e_t m_in_button;
    pros::controller_digital_e_t m_out_button;
    pros::controller_digital_e_t m_secondary_button;

    std::string m_handle_name;

    bool m_open = false;
    bool m_toggle = false;
    bool m_running = false;
    bool m_inButtonPreivousState = false;

public:
    IntakeNode(NodeManager* node_manager, std::string handle_name, ControllerNode* controller, MotorNode* intake_motor, pros::controller_digital_e_t in_button, bool toggle);

    IntakeNode(NodeManager* node_manager, std::string handle_name, ControllerNode* controller, MotorNode* intake_motor, pros::controller_digital_e_t in_button, pros::controller_digital_e_t out_button);

    IntakeNode(NodeManager* node_manager, std::string handle_name, ControllerNode* controller, MotorNode* intake_motor, MotorNode* intake_motor2, pros::controller_digital_e_t in_button, pros::controller_digital_e_t out_button, pros::controller_digital_e_t secondary_button);

    void setIntakeVoltage(int voltage);
    
    void setIntakeVelocity(float velocity);

    void initialize();

    void teleopPeriodic();

    void autonPeriodic();

    ~IntakeNode();
};
