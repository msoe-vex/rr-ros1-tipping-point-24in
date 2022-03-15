#pragma once

#include "lib-rr/nodes/NodeManager.h"
#include "lib-rr/nodes/subsystems/IClawNode.h"
#include "lib-rr/nodes/sensor_nodes/ControllerNode.h"
#include "lib-rr/nodes/actuator_nodes/ADIDigitalOutNode.h"
#include "pros/misc.h"

class ClawNode : public IClawNode {
private:
    ControllerNode* m_controller;
    ADIDigitalOutNode* m_claw;
    pros::controller_digital_e_t m_button;
    bool m_claw_open;
    bool m_a_previous_state;

    
public:
    ClawNode(NodeManager* node_manager, std::string handle_name, ControllerNode* controller,
    ADIDigitalOutNode* claw, pros::controller_digital_e_t button) ;

    void initialize();

    void useClaw(bool opened);

    void teleopPeriodic();

    void autonPeriodic();

    ~ClawNode();
};