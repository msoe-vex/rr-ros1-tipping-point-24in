#pragma once

#include "lib-rr/nodes/NodeManager.h"
#include "lib-rr/nodes/subsystems/ILiftNode.h"
#include "lib-rr/nodes/sensor_nodes/ControllerNode.h"
#include "lib-rr/nodes/actuator_nodes/MotorNode.h"
#include "lib-rr/nodes/sensor_nodes/ADIAnalogInNode.h"
#include "pros/misc.h"
#include "lib-rr/util/PID.h"

class HighRungLiftNode : public ILiftNode {
public:
    enum HighRungLiftState {
        LOADING, STRAIGHT_UP, SCORING, FREE_MOVING
    };

    HighRungLiftNode(NodeManager* node_manager, std::string handle_name, 
        ControllerNode* controller, pros::controller_analog_e_t joystick, pros::controller_digital_e_t preset_btn, 
        MotorNode* motor, ADIAnalogInNode* potentiometer);
    
    void initialize();

    void setLiftVoltage(int voltage);

    void setLiftVelocity(float velocity);

    void setLiftPosition(int position, int tolerance = 5);
    
    void setLiftState(HighRungLiftState state);

    int getPosition();

    void teleopPeriodic();

    void autonPeriodic();

    ~HighRungLiftNode();

private:    
    void m_setLiftPID();

    void m_updateLiftStateTeleop();

    void m_goToClosestState();

    ControllerNode* m_controller;
    MotorNode* m_motor;
    ADIAnalogInNode* m_potentiometer;
    pros::controller_analog_e_t m_joystick;
    pros::controller_digital_e_t m_preset_btn;
    HighRungLiftState m_state;

    PID m_lift_pid;

    bool m_freeMoving = false;

    int m_loadingPosition = 440;
    int m_straightUpPosition = 2400;
    int m_scoringPosition = 3000;

    int m_target_position;
    int m_tolerance;
};