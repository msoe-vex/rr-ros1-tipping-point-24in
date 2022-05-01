#pragma once

#include "lib-rr/auton/Auton.h"
#include "lib-rr/nodes/subsystems/IDriveNode.h"
#include "lib-rr/nodes/odometry_nodes/OdometryNode.h"
#include "lib-rr/nodes/sensor_nodes/InertialSensorNode.h"
#include "lib-rr/auton/auton_actions/DriveStraightAction.h"
#include "auton/auton_actions/PlatformBalance.h"
#include "lib-rr/auton/auton_actions/UseClawAction.h"
#include "lib-rr/auton/auton_actions/MoveLiftToPositionAction.h"
#include "lib-rr/auton/auton_actions/RollerIntakeAction.h"
#include "lib-rr/auton/auton_actions/FollowPathAction.h"
#include "auton/auton_actions/SetBackClawStateAction.h"
#include "lib-rr/pursuit/path_pursuit/TankPathPursuit.h"
#include "lib-rr/nodes/subsystems/ILiftNode.h"
#include "lib-rr/nodes/subsystems/IClawNode.h"
#include "lib-rr/nodes/subsystems/IRollerIntakeNode.h"
#include "auton/auton_actions/DeployAction.h"
#include "auton/auton_actions/SetLiftStateAction.h"
#include "lib-rr/pathing/PathManager.h"
#include "lib-rr/math/Pose.h"
#include "lib-rr/util/Constants.h"
#include "lib-rr/eigen/Eigen/Dense"
#include "nodes/BackClawNode.h"
#include "nodes/LiftNode.h"
#include "nodes/HighRungLiftNode.h"


class ProgrammingSkillzAuton : public Auton {
public:
    ProgrammingSkillzAuton(IDriveNode* driveNode, OdometryNode* odomNode, IRollerIntakeNode* intakeNode, 
        IRollerIntakeNode* conveyorNode, IRollerIntakeNode* flapConveyorNode, IClawNode* frontClawNode, 
        BackClawNode* backClaw, IClawNode* wingArms, IClawNode* buddyClimb, LiftNode* liftNode, 
        HighRungLiftNode* highRungLiftNode);

    void AddNodes();

private:
    IDriveNode* m_driveNode;
    OdometryNode* m_odomNode;
    IRollerIntakeNode* m_intakeNode;
    IRollerIntakeNode* m_conveyorNode;
    IRollerIntakeNode* m_flapConveyorNode;
    IClawNode* m_frontClawNode;
    BackClawNode* m_backClaw;
    IClawNode* m_wingArms;
    IClawNode* m_buddyClimb;
    LiftNode* m_liftNode;
    HighRungLiftNode* m_highRungLiftNode;

};