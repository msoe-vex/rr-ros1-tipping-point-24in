#include "main.h"

NodeManager* nodeManager;

AutonManagerNode* autonManagerNode;

ControllerNode* controller;

TankDriveNode* tankDriveNode;
MotorNode* leftFrontTopMotor;
MotorNode* leftFrontBottomMotor;
MotorNode* leftRearTopMotor;
MotorNode* leftRearBottomMotor;
MotorNode* rightFrontTopMotor;
MotorNode* rightFrontBottomMotor;
MotorNode* rightRearTopMotor;
MotorNode* rightRearBottomMotor;

MotorNode* intakeMotor;
IntakeNode* intakeNode;

MotorNode* conveyorMotor;
IntakeNode* conveyorNode;

MotorNode* flapConveyorMotor;
IntakeNode* flapConveyorNode;

ClawNode* frontClaw;
ADIDigitalOutNode* frontClawPiston;

ClawNode* backClaw;
ADIDigitalOutNode* backClawPiston;

ClawNode* backTilt;
ADIDigitalOutNode* backTiltPiston;

LiftNode* liftNode;
MotorNode* leftLiftMotor;
MotorNode* rightLiftMotor;

ADIEncoderNode* yOdomEncoder;
ADIEncoderNode* xOdomEncoder;

InertialSensorNode* inertialSensor;

OdometryNode* odomNode;

// Declare all robot nodes here:

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	// Create the node manager
	nodeManager = new NodeManager(pros::millis);

	// Initialize a static logger
	Logger::giveNodeManager(nodeManager);

	// Initialize all robot nodes here:

	controller = new ControllerNode(nodeManager, "controller");

	/* Define the odometry components */
	xOdomEncoder = new ADIEncoderNode(nodeManager, 'A', 'B', "xOdomEncoder", false);
	yOdomEncoder = new ADIEncoderNode(nodeManager, 'C', 'D', "yOdomEncoder", false);

	inertialSensor = new InertialSensorNode(nodeManager, "inertialSensor", 20);

	odomNode = new OdometryNode(nodeManager, "odometry", xOdomEncoder, 
	yOdomEncoder, inertialSensor, OdometryNode::FOLLOWER);

	leftFrontTopMotor = new MotorNode(nodeManager, 21, "leftFrontTopMotor", true);
	leftFrontBottomMotor = new MotorNode(nodeManager, 15, "leftFrontBottomMotor", true);
	leftRearTopMotor = new MotorNode(nodeManager, 1, "leftRearTopMotor", true);
	leftRearBottomMotor = new MotorNode(nodeManager, 11, "leftRearBottomMotor", true);
	rightFrontTopMotor = new MotorNode(nodeManager, 18, "rightFrontTopMotor", false);
	rightFrontBottomMotor = new MotorNode(nodeManager, 17, "rightFrontBottomMotor", false);
	rightRearTopMotor = new MotorNode(nodeManager, 12, "rightRearTopMotor", false);
	rightRearBottomMotor = new MotorNode(nodeManager, 2, "rightRearBottomMotor", false);

	TankDriveNode::TankEightMotors tankMotors = {
		leftFrontTopMotor,
		leftFrontBottomMotor,
		leftRearTopMotor,
		leftRearBottomMotor,
		rightFrontTopMotor,
		rightFrontTopMotor,
		rightRearTopMotor,
		rightRearBottomMotor
	};

	TankDriveKinematics::TankWheelLocations wheelLocations = {
		Vector2d(0, 0),
		Vector2d(0, 0)
	};

	EncoderConfig encoderConfig = {
		0, // Initial ticks
		2400, // Ticks per RPM
		1.975 // Wheel diameter
	};

	TankDriveKinematics tankKinematics(encoderConfig, wheelLocations);

	tankDriveNode = new TankDriveNode(nodeManager, "tank_drive_node", controller, 
        tankMotors, tankKinematics
	);

	intakeMotor = new MotorNode(nodeManager, 14, "intakeMotor", true);
	intakeNode = new IntakeNode(nodeManager, "intakeNode", controller, intakeMotor, pros::E_CONTROLLER_DIGITAL_L1);
	
	flapConveyorMotor = new MotorNode(nodeManager, 9, "conveyorMotor", false);
	flapConveyorNode = new IntakeNode(nodeManager, "conveyorNode", controller, flapConveyorMotor, pros::E_CONTROLLER_DIGITAL_Y, pros::E_CONTROLLER_DIGITAL_A);

	conveyorMotor = new MotorNode(nodeManager, 19, "conveyorMotor", false);
	conveyorNode = new IntakeNode(nodeManager, "conveyorNode", controller, conveyorMotor, pros::E_CONTROLLER_DIGITAL_L1, pros::E_CONTROLLER_DIGITAL_L2);

	leftLiftMotor = new MotorNode(nodeManager, 16, "leftLiftMotor", false);
	rightLiftMotor = new MotorNode(nodeManager, 10, "rightLiftMotor", true);
	//bottom_limit_switch_lift = new ADIDigitalInNode(node_manager, 7, "bottom_limit_switch_lift");
	//top_limit_switch_lift = new ADIDigitalInNode(node_manager, 6, "top_limit_switch_lift");
	//potentiometer_lift = new ADIAnalogInNode(node_manager, 8, "potentiometer_lift", false);

	liftNode = new LiftNode(
		nodeManager, 
		"liftNode", 
        controller, 
		leftLiftMotor, 
        rightLiftMotor,
		pros::E_CONTROLLER_DIGITAL_R1,
		pros::E_CONTROLLER_DIGITAL_R2
	);

	frontClawPiston = new ADIDigitalOutNode(nodeManager, "frontClawPiston", 'G', false);

	frontClaw = new ClawNode(nodeManager, "frontClaw", controller, frontClawPiston, pros::E_CONTROLLER_DIGITAL_B);

	backClawPiston = new ADIDigitalOutNode(nodeManager, "backClawPiston", 'E', false);

	backClaw = new ClawNode(nodeManager, "backClaw", controller, backClawPiston, pros::E_CONTROLLER_DIGITAL_LEFT);

	backTiltPiston = new ADIDigitalOutNode(nodeManager, "backTiltPiston", 'F', false);
	backTilt = new ClawNode(nodeManager, "backTilt", controller, backTiltPiston, pros::E_CONTROLLER_DIGITAL_DOWN);
	
	// Initialize the autonomous manager
	autonManagerNode = new AutonManagerNode(nodeManager, tankDriveNode, yOdomEncoder, inertialSensor);

	// Call the node manager to initialize all of the nodes above
	nodeManager->initialize();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
	while (pros::competition::is_disabled()) {
		nodeManager->m_handle->spinOnce();
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
	nodeManager->reset();

	// Reset the chosen autonomous and initialize
	autonManagerNode->selected_auton->AutonInit();
	
	// Execute autonomous code
	while (pros::competition::is_autonomous()) {
		nodeManager->executeAuton();
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
	nodeManager->reset();
	
	// Execute teleop code
	while (true) {
		nodeManager->executeTeleop();
	}
}
