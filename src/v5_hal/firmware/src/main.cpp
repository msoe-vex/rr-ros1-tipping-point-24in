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

ClawNode* rightclaw;
ADIDigitalOutNode* right_claw_piston;

ClawNode* leftclaw;
ADIDigitalOutNode* left_claw_piston;

ClawNode* backclaw;
ADIDigitalOutNode* back_claw_piston;

ClawNode* pivotclaw;
ADIDigitalOutNode* pivot_claw_piston;


LiftNode* left_lift_node;
MotorNode* left_motor_lift;

LiftNode* right_lift_node;
MotorNode* right_motor_lift;


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

	left_1_motor = new MotorNode(node_manager, 1,"left_1_motor", false);
	left_2_motor = new MotorNode(node_manager, 2,"left_2_motor", true);
	left_3_motor = new MotorNode(node_manager, 3,"left_3_motor", true);
	left_4_motor = new MotorNode(node_manager, 4,"left_4_motor", false);
	right_1_motor = new MotorNode(node_manager, 5,"right_1_motor", true);
	right_2_motor = new MotorNode(node_manager, 6,"right_2_motor", false);
	right_3_motor = new MotorNode(node_manager, 7,"right_3_motor", false);
	right_4_motor = new MotorNode(node_manager, 8,"right_4_motor", true);

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
		0,
		900,
		4.0
	};

	TankDriveKinematics tank_kinematics(encoder_config, wheel_locations);

	tank_drive_node = new TankDriveNode(node_manager, "tank_drive_node", controller, 
        tank_motors, tank_kinematics
	);
	
	left_motor_lift = new MotorNode(node_manager, 10, "left_motor_lift", true);
	right_motor_lift = new MotorNode(node_manager, 15, "right_motor_lift", false);


	left_lift_node = new LiftNode(node_manager, "left_lift_node", 
        controller, left_motor_lift, pros::E_CONTROLLER_DIGITAL_L1, pros::E_CONTROLLER_DIGITAL_L2
	);

	right_lift_node = new LiftNode(node_manager, "right_lift_node", 
        controller, right_motor_lift, pros::E_CONTROLLER_DIGITAL_R1, pros::E_CONTROLLER_DIGITAL_R2
	);

	right_claw_piston = new ADIDigitalOutNode(node_manager, "primary_claw_piston", 3, false);
	left_claw_piston = new ADIDigitalOutNode(node_manager, "secondary_claw_piston", 1, false);
	back_claw_piston = new ADIDigitalOutNode(node_manager, "back_claw_piston", 2, false);
	pivot_claw_piston = new ADIDigitalOutNode(node_manager, "pivot_claw_piston", 4, false);

	rightclaw = new ClawNode(node_manager, "rightclaw", controller, right_claw_piston, pros::E_CONTROLLER_DIGITAL_X);
	leftclaw = new ClawNode(node_manager, "leftclaw", controller, left_claw_piston, pros::E_CONTROLLER_DIGITAL_UP);
	backclaw = new ClawNode(node_manager, "back_claw", controller, back_claw_piston, pros::E_CONTROLLER_DIGITAL_DOWN);
	pivotclaw = new ClawNode(node_manager, "pivot_claw", controller, pivot_claw_piston, pros::E_CONTROLLER_DIGITAL_B);

	// Initialize the autonomous manager
	auton_manager_node = new AutonManagerNode(node_manager, tank_drive_node, pivotclaw, right_lift_node);

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
