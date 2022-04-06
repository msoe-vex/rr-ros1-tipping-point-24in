#include "nodes/auton_nodes/AutonManagerNode.h"

AutonManagerNode::AutonManagerNode(NodeManager* node_manager, IDriveNode* drive_node, OdometryNode* odom_node, InertialSensorNode* inertial_sensor_node) : 
        Node(node_manager, 50),
        m_drive_node(drive_node),
        m_odom_node(odom_node),
        m_inertial_sensor_node(inertial_sensor_node) {
    m_test_auton = new odomTest(m_drive_node, m_odom_node, m_inertial_sensor_node);
    selected_auton = m_test_auton;
}

void AutonManagerNode::initialize() {
    //PathManager::GetInstance()->LoadPathsFile("/usd/path.json");
}

void AutonManagerNode::autonPeriodic() {
    if(!selected_auton->Complete()) {
        selected_auton->AutonPeriodic();
    }
}