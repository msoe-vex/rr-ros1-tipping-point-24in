#include "nodes/auton_nodes/AutonManagerNode.h"

AutonManagerNode::AutonManagerNode(NodeManager* node_manager, OdometryNode* odom_node, 
        IDriveNode* drive_node, IClawNode* front_claw_node, HighRungLiftNode* high_rung_lift_node) : 
        Node(node_manager, 50),
        m_odomNode(odom_node),
        m_driveNode(drive_node),
        m_frontClawNode(front_claw_node),
        m_high_rung_lift_node(high_rung_lift_node) {
    m_match_auton = new BasicAuton(m_driveNode, m_odomNode, m_high_rung_lift_node);
    selected_auton = m_match_auton;
}

void AutonManagerNode::initialize() {
    PathManager::GetInstance()->LoadPathsFile("/usd/path24inProgPt2.json");
}

void AutonManagerNode::autonPeriodic() {
    if(!selected_auton->Complete()) {
        selected_auton->AutonPeriodic();
    }
}