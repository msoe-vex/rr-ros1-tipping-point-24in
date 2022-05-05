#include "main.h"

NodeManager* nodeManager;

AutonManagerNode* autonManagerNode;

ControllerNode* controller1;
ControllerNode* controller2;

TankDriveNode* tankDriveNode;
MotorNode* left1Motor;
MotorNode* left2Motor;
MotorNode* left3Motor;
MotorNode* left4Motor;
MotorNode* right1Motor;
MotorNode* right2Motor;
MotorNode* right3Motor;
MotorNode* right4Motor;

MotorNode* intakeMotor;
IntakeNode* intakeNode;

MotorNode* conveyorMotor;
IntakeNode* conveyorNode;

MotorNode* spindexerMotor;
MotorNode* flapConveyorMotor;
IntakeNode* flapConveyorNode;

ClawNode* frontClaw;
ADIDigitalOutNode* frontClawPiston;

MotorNode* goalSpinnerMotor;
GoalSpinnerNode* goalSpinner;

BackClawNode* backClaw;
ADIDigitalOutNode* backClawPiston;
ADIDigitalOutNode* backTiltPiston;

ClawNode* wingArm;
ADIDigitalOutNode* wingArmPiston;

ADIDigitalOutNode* buddyClimbPiston;
ClawNode* buddyClimb;

LiftNode* liftNode;
MotorNode* leftLiftMotor;
MotorNode* rightLiftMotor;
ADIDigitalInNode* liftBottomLimitSwitch;
ADIDigitalInNode* liftTopLimitSwitch;
ADIAnalogInNode* liftPotentiometer;

MotorNode* highRungLiftMotor;
ADIAnalogInNode* highRungLiftPotentiometer;
HighRungLiftNode* highRungLift;

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

	controller1 = new ControllerNode(nodeManager, "controller1");
	controller2 = new ControllerNode(nodeManager, "controller2", pros::E_CONTROLLER_PARTNER);

	/* Define the odometry components */
	xOdomEncoder = new ADIEncoderNode(nodeManager, {3, 'C', 'D'}, "xOdomEncoder", false);
	yOdomEncoder = new ADIEncoderNode(nodeManager, {3, 'A', 'B'}, "yOdomEncoder", true);

	inertialSensor = new InertialSensorNode(nodeManager, "inertialSensor", 20);

	IOdometry::EncoderLocations encoderLocations {
		Vector2d(-0.008, -4.882),
		Vector2d(1.556, -1.263)
	};

	odomNode = new OdometryNode(nodeManager, "odometry", xOdomEncoder, 
	yOdomEncoder, inertialSensor, OdometryNode::FOLLOWER, encoderLocations);

	left1Motor = new MotorNode(nodeManager, 11, "leftFrontTopMotor", false);
	left2Motor = new MotorNode(nodeManager, 1, "leftFrontBottomMotor", true);
	left3Motor = new MotorNode(nodeManager, 15, "leftRearTopMotor", true);
	left4Motor = new MotorNode(nodeManager, 21, "leftRearBottomMotor", false);
	right1Motor = new MotorNode(nodeManager, 12, "rightFrontTopMotor", true);
	right2Motor = new MotorNode(nodeManager, 2, "rightFrontBottomMotor", false);
	right3Motor = new MotorNode(nodeManager, 18, "rightRearTopMotor", false);
	right4Motor = new MotorNode(nodeManager, 17, "rightRearBottomMotor", true);

	TankDriveNode::TankEightMotors tankMotors = {
		left1Motor,
		left2Motor,
		left3Motor,
		left4Motor,
		right1Motor,
		right2Motor,
		right3Motor,
		right4Motor
	};

	TankDriveKinematics::TankWheelLocations wheelLocations = {
		Vector2d(0, 0),
		Vector2d(0, 0)
	};

	EncoderConfig encoderConfig = {
		0, // Initial ticks
		2400, // Ticks per RPM
		1.975, // Wheel diameter
	};

	TankDriveKinematics tankKinematics(encoderConfig, wheelLocations);

	tankDriveNode = new TankDriveNode(nodeManager, "tank_drive_node", controller1, 
        tankMotors, tankKinematics
	);

	intakeMotor = new MotorNode(nodeManager, 14, "intakeMotor", true);
	intakeNode = new IntakeNode(nodeManager, "intakeNode", controller2, intakeMotor, DIGITAL_A, true);
	
	spindexerMotor = new MotorNode(nodeManager, 8, "spindexerMotor", false);
	flapConveyorMotor = new MotorNode(nodeManager, 9, "conveyorMotor", false);
	flapConveyorNode = new IntakeNode(nodeManager, "conveyorNode", controller2, flapConveyorMotor, spindexerMotor, pros::E_CONTROLLER_DIGITAL_R1, pros::E_CONTROLLER_DIGITAL_R2);

	conveyorMotor = new MotorNode(nodeManager, 19, "conveyorMotor", false);
	conveyorNode = new IntakeNode(nodeManager, "conveyorNode", controller2, conveyorMotor, pros::E_CONTROLLER_DIGITAL_L1, pros::E_CONTROLLER_DIGITAL_L2);

	leftLiftMotor = new MotorNode(nodeManager, 16, "leftLiftMotor", false);
	rightLiftMotor = new MotorNode(nodeManager, 10, "rightLiftMotor", true);
	liftBottomLimitSwitch = new ADIDigitalInNode(nodeManager, 'F', "liftBottomLimitSwitch"); // not on robot
	liftTopLimitSwitch = new ADIDigitalInNode(nodeManager, 'H', "liftTopLimitSwitch");//now a button switch
	liftPotentiometer = new ADIAnalogInNode(nodeManager, 'A', "liftPotentiometer", false); // actually on robot but probably not accurate port
	
	liftNode = new LiftNode(
		nodeManager, 
		"liftNode", 
        controller1, 
		DIGITAL_R1,
		DIGITAL_R2,
		DIGITAL_X,
		leftLiftMotor, 
        rightLiftMotor,
		liftBottomLimitSwitch,
		liftTopLimitSwitch,
		liftPotentiometer
	);

	highRungLiftMotor = new MotorNode(nodeManager, 6, "highRungLiftMotor", true);
	highRungLiftPotentiometer = new ADIAnalogInNode(nodeManager, 'B', "highRungLiftPotentiometer", false); 
	highRungLift = new HighRungLiftNode(
		nodeManager, 
		"highRungLift", 
		controller2, 
		ANALOG_LEFT_Y, 
		highRungLiftMotor, 
		highRungLiftPotentiometer
	);

	frontClawPiston = new ADIDigitalOutNode(nodeManager, "frontClawPiston", 'G', false, true);

	frontClaw = new ClawNode(nodeManager, "frontClaw", controller1, frontClawPiston, 
		DIGITAL_L1);

	goalSpinnerMotor = new MotorNode(nodeManager, 5, "goalSpinnerMotor", true);
	goalSpinner = new GoalSpinnerNode(nodeManager, "goalSpinner", controller1, DIGITAL_A, DIGITAL_Y, goalSpinnerMotor);

	backClawPiston = new ADIDigitalOutNode(nodeManager, "backClawPiston", 'F', false, true);

	backTiltPiston = new ADIDigitalOutNode(nodeManager, "backTiltPiston", 'E', false, true);

	backClaw = new BackClawNode(nodeManager, "backClaw", controller1, DIGITAL_L2, 
		DIGITAL_DOWN, backTiltPiston, backClawPiston);
	
	buddyClimbPiston = new ADIDigitalOutNode(nodeManager, "buddyClimbPiston", 'C', false, true);
	buddyClimb = new ClawNode(nodeManager, "buddyClimb", controller1, buddyClimbPiston, DIGITAL_UP, DIGITAL_RIGHT);

	// Define auton nodes
    LeftAuton* leftAuton = new LeftAuton(
		tankDriveNode, 
		odomNode, 
		frontClaw, 
        liftNode, 
		highRungLift, 
		backClaw, 
		intakeNode, 
		conveyorNode, 
		flapConveyorNode
	);

	ProgrammingSkillzAuton* progSkills = new ProgrammingSkillzAuton(
		tankDriveNode,
		odomNode,
		intakeNode,
		conveyorNode,
		flapConveyorNode,
		frontClaw,
		backClaw,
		buddyClimb,
		liftNode,
		highRungLift,
		goalSpinner
	);

	BasicAuton* basicAuton = new BasicAuton(
		tankDriveNode,
		odomNode,
		highRungLift,
		goalSpinner,
		liftNode
	);
	
	std::vector<Auton*> autons = {
		leftAuton,
		progSkills,
		basicAuton
	};
	
	// Initialize the autonomous manager
	autonManagerNode = new AutonManagerNode(nodeManager, autons);

	// Call the node manager to initialize all of the nodes above
	nodeManager->initialize();
	
	// controller selection menus
	bool needsPath = selectAuton(controller1, autonManagerNode);
	pros::delay(500);
	if (needsPath) {
		selectPathJSON(controller1, autonManagerNode);
		pros::delay(500);
	}
	controller1->updateDisplay("Selection Complete");
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
