#include "nodes/auton_nodes/AutonManagerNode.h"

AutonManagerNode::AutonManagerNode(NodeManager* nodeManager, IDriveNode* driveNode, OdometryNode* odomNode, IRollerIntakeNode* intakeNode, IRollerIntakeNode* conveyorNode, IRollerIntakeNode* flapConveyorNode, IClawNode* frontClawNode, BackClawNode* backClaw, IClawNode* wingArms, IClawNode* buddyClimb, LiftNode* liftNode, HighRungLiftNode* highRungLiftNode): 
        Node(nodeManager, 50),
        m_driveNode(driveNode),
        m_odomNode(odomNode),
        m_intakeNode(intakeNode),
        m_conveyorNode(conveyorNode),
        m_flapConveyorNode(flapConveyorNode),
        m_frontClawNode(frontClawNode),
        m_backClaw(backClaw),
        m_wingArms(wingArms),
        m_buddyClimb(buddyClimb),
        m_liftNode(liftNode),
        m_highRungLiftNode(highRungLiftNode) {
    m_match_auton = new BasicAuton(m_driveNode, m_odomNode, m_highRungLiftNode);
    m_prog_skills = new ProgrammingSkillzAuton(m_driveNode, m_odomNode, m_intakeNode, m_conveyorNode, m_flapConveyorNode, m_frontClawNode, m_backClaw, m_wingArms, m_buddyClimb, m_liftNode, m_highRungLiftNode);
    selected_auton = m_prog_skills;
}

void AutonManagerNode::initialize() {
    PathManager::GetInstance()->LoadPathsFile("/usd/path24inProgPt2.json");
}

void AutonManagerNode::autonPeriodic() {
    if(!selected_auton->Complete()) {
        selected_auton->AutonPeriodic();
    }
}