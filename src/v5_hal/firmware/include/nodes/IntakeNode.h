#pragma once

#include "lib-rr/nodes/NodeManager.h"
#include "api.h"
#include "lib-rr/nodes/actuator_nodes/MotorNode.h"
#include "lib-rr/nodes/sensor_nodes/ControllerNode.h"
#include "lib-rr/nodes/actuator_nodes/ADIDigitalOutNode.h"
#include "lib-rr/util/Constants.h"

class IntakeNode : public Node {
private:
    pros::Controller* m_controller;
    MotorNode* m_intake_motor;

    bool m_canReverse = false;
    pros::controller_digital_e_t m_in_button;
    pros::controller_digital_e_t m_out_button;

    std::string m_handle_name;

    bool m_open = false;

public:
    IntakeNode(NodeManager* node_manager, std::string handle_name, ControllerNode* controller, MotorNode* intake_motor, pros::controller_digital_e_t in_button);

    IntakeNode(NodeManager* node_manager, std::string handle_name, ControllerNode* controller, MotorNode* intake_motor, pros::controller_digital_e_t in_button, pros::controller_digital_e_t out_button);

    void setIntakeVoltage(int voltage);

    void initialize();

    void teleopPeriodic();

    void autonPeriodic();

    ~IntakeNode();
};
