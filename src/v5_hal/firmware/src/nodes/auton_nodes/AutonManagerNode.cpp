#include "nodes/auton_nodes/AutonManagerNode.h"

AutonManagerNode::AutonManagerNode(NodeManager* node_manager, OdometryNode* odom_node, IDriveNode* drive_node, IClawNode* front_claw_node, ILiftNode* lift_node, IRollerIntakeNode* intake_node) : 
        Node(node_manager, 50),
        m_odomNode(odom_node),
        m_driveNode(drive_node),
        m_frontClawNode(front_claw_node),
        m_liftNode(lift_node),
        m_intakeNode(intake_node) {
    m_match_auton = new MatchAuton(m_driveNode, m_odomNode, m_frontClawNode, m_liftNode, m_intakeNode);
    selected_auton = m_match_auton;
}

void AutonManagerNode::initialize() {
    PathManager::GetInstance()->LoadPathsFile("/usd/path.json");
}

void AutonManagerNode::autonPeriodic() {
    if(!selected_auton->Complete()) {
        selected_auton->AutonPeriodic();
    }
}