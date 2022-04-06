#include "main.h"

NodeManager* node_manager;

AutonManagerNode* auton_manager_node;

ControllerNode* controller;

TankDriveNode* tank_drive_node;
MotorNode* left_1_motor;
MotorNode* left_2_motor;
MotorNode* left_3_motor;
MotorNode* left_4_motor;
MotorNode* right_1_motor;
MotorNode* right_2_motor;
MotorNode* right_3_motor;
MotorNode* right_4_motor;

MotorNode* intake_motor;
IntakeNode* intake_node;

ADIEncoderNode* y_odom_encoder;
ADIEncoderNode* x_odom_encoder;

InertialSensorNode* inertial_sensor;

OdometryNode* odom_node;

// Declare all robot nodes here:

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	// Create the node manager
	node_manager = new NodeManager(pros::millis);

	// Initialize a static logger
	Logger::giveNodeManager(node_manager);

	// Initialize all robot nodes here:

	controller = new ControllerNode(node_manager, "controller");

	/* Define the odometry components */
	x_odom_encoder = new ADIEncoderNode(node_manager, 'A', 'B', "xOdomEncoder", false);
	y_odom_encoder = new ADIEncoderNode(node_manager, 'C', 'D', "yOdomEncoder", false);

	inertial_sensor = new InertialSensorNode(node_manager, "inertialSensor", 14);

	odom_node = new OdometryNode(node_manager, "odometry", x_odom_encoder, 
	y_odom_encoder, inertial_sensor, OdometryNode::FOLLOWER);

	left_1_motor = new MotorNode(node_manager, 4, "left_1_motor", false);
	left_2_motor = new MotorNode(node_manager, 3, "left_2_motor", true);
	left_3_motor = new MotorNode(node_manager, 2, "left_3_motor", true);
	left_4_motor = new MotorNode(node_manager, 1, "left_4_motor", false);
	right_1_motor = new MotorNode(node_manager, 14, "right_1_motor", true);
	right_2_motor = new MotorNode(node_manager, 13, "right_2_motor", false);
	right_3_motor = new MotorNode(node_manager, 12, "right_3_motor", false);
	right_4_motor = new MotorNode(node_manager, 11, "right_4_motor", true);

	TankDriveNode::TankEightMotors tank_motors = {
		left_1_motor,
		left_2_motor,
		left_3_motor,
		left_4_motor,
		right_1_motor,
		right_2_motor,
		right_3_motor,
		right_4_motor
	};

	TankDriveKinematics::TankWheelLocations wheel_locations = {
		Vector2d(0, 0),
		Vector2d(0, 0)
	};

	EncoderConfig encoder_config = {
		0, // Initial ticks
		2400, // Ticks per RPM
		1.975 // Wheel diameter
	};

	TankDriveKinematics tank_kinematics(encoder_config, wheel_locations);

	tank_drive_node = new TankDriveNode(node_manager, "tank_drive_node", controller, 
        tank_motors, tank_kinematics
	);

	intake_motor = new MotorNode(node_manager, 5, "intake_motor", true);
	intake_node = new IntakeNode(node_manager, "intakeNode", controller, intake_motor);
	
	// Initialize the autonomous manager
	auton_manager_node = new AutonManagerNode(node_manager, tank_drive_node, odom_node);

	// Call the node manager to initialize all of the nodes above
	node_manager->initialize();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
	while (pros::competition::is_disabled()) {
		node_manager->m_handle->spinOnce();
	}
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	// Reset all nodes to default configuration
	node_manager->reset();

	// Reset the chosen autonomous and initialize
	auton_manager_node->selected_auton->AutonInit();
	
	// Execute autonomous code
	while (pros::competition::is_autonomous()) {
		node_manager->executeAuton();
	}
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 *
 * NOTE: If custom code is needed outside of the node manager, it should be put
 * into a different task with a wait. Each node has an embedded timing control loop
 * and adding a wait to this thread will disrupt the performance of all nodes.
 */
void opcontrol() {
	// Reset all nodes to default configuration
	node_manager->reset();
	
	// Execute teleop code
	while (true) {
		node_manager->executeTeleop();
	}
}
