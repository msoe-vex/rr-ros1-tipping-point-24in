#include "nodes/auton_nodes/AutonManagerNode.h"

AutonManagerNode::AutonManagerNode(NodeManager* node_manager, OdometryNode* odom_node, IDriveNode* drive_node, 
            ADIEncoderNode* y_odom_encoder, InertialSensorNode* inertial_sensor) : 
        Node(node_manager, 50),
        m_odom_node(odom_node),
        m_drive_node(drive_node),
        m_y_odom_encoder(y_odom_encoder),
        m_inertial_sensor(inertial_sensor) {
    m_basic_auton = new BasicAuton(m_drive_node, m_odom_node, m_y_odom_encoder, m_inertial_sensor);
    selected_auton = m_basic_auton;
}

void AutonManagerNode::initialize() {
    //PathManager::GetInstance()->LoadPathsFile("/usd/path.json");
}

void AutonManagerNode::autonPeriodic() {
    if(!selected_auton->Complete()) {
        selected_auton->AutonPeriodic();
    }
}