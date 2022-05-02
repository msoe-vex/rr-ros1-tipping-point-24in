#include "nodes/auton_nodes/AutonManagerNode.h"

AutonManagerNode::AutonManagerNode(NodeManager* node_manager, OdometryNode* odomNode, 
        IDriveNode* driveNode, IClawNode* frontClawNode, HighRungLiftNode* highRungLiftNode,
        IRollerIntakeNode* intakeNode, IRollerIntakeNode* conveyorNode, IRollerIntakeNode* flapConveyorNode, 
        BackClawNode* backClaw, IClawNode* buddyClimb, LiftNode* liftNode) : 
        Node(node_manager, 50),
        m_odomNode(odomNode),
        m_driveNode(driveNode),
        m_frontClawNode(frontClawNode),
        m_intakeNode(intakeNode),
        m_conveyorNode(conveyorNode),
        m_flapConveyorNode(flapConveyorNode),
        m_backClaw(backClaw),
        m_buddyClimb(buddyClimb),
        m_liftNode(liftNode),
        m_highRungLiftNode(highRungLiftNode) {
    m_match_auton = new BasicAuton(m_driveNode, m_odomNode, m_highRungLiftNode);
    m_prog_skills = new ProgrammingSkillzAuton(m_driveNode, m_odomNode, m_intakeNode, m_conveyorNode, 
        m_flapConveyorNode, m_frontClawNode, m_backClaw, m_buddyClimb, m_liftNode, m_highRungLiftNode);
    selected_auton = m_match_auton;
}

void AutonManagerNode::initialize() {
    PathManager::GetInstance()->LoadPathsFile("/usd/24inLeft.json");
}

void AutonManagerNode::autonPeriodic() {
    if(!selected_auton->Complete()) {
        selected_auton->AutonPeriodic();
    }
}