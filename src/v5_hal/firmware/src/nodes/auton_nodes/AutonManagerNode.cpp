#include "nodes/auton_nodes/AutonManagerNode.h"

AutonManagerNode::AutonManagerNode(NodeManager* node_manager, OdometryNode* odom_node,
        IDriveNode* drive_node, IClawNode* front_claw_node, LiftNode* liftNode, HighRungLiftNode* highRungLiftNode,
        BackClawNode* backClawNode, IRollerIntakeNode* intakeNode, IRollerIntakeNode* conveyorNode, IRollerIntakeNode* flapConveyorNode) : 
        Node(node_manager, 50),
        m_odomNode(odom_node),
        m_driveNode(drive_node),
        m_frontClawNode(front_claw_node),
        m_liftNode(liftNode),
        m_highRungLiftNode(highRungLiftNode),
        m_backClawNode(backClawNode),
        m_intakeNode(intakeNode),
        m_conveyorNode(conveyorNode),
        m_flapConveyorNode(flapConveyorNode) {
    m_match_auton = new MatchAuton(m_driveNode, m_odomNode, m_frontClawNode);
    m_leftAuton = new LeftAuton(m_driveNode, m_odomNode, m_frontClawNode, 
        m_liftNode, m_highRungLiftNode, m_backClawNode, m_intakeNode, m_conveyorNode, m_flapConveyorNode);
    selected_auton = m_leftAuton;
}

void AutonManagerNode::initialize() {
    PathManager::GetInstance()->LoadPathsFile("/usd/24inLeft.json");
}

void AutonManagerNode::autonPeriodic() {
    if(!selected_auton->Complete()) {
        selected_auton->AutonPeriodic();
    }
}