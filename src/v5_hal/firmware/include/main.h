/**
 * \file main.h
 *
 * Contains common definitions and header files used throughout your PROS
 * project.
 *
 * Copyright (c) 2017-2020, Purdue University ACM SIGBots.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_

 /**
  * If defined, some commonly used enums will have preprocessor macros which give
  * a shorter, more convenient naming pattern. If this isn't desired, simply
  * comment the following line out.
  *
  * For instance, E_CONTROLLER_MASTER has a shorter name: CONTROLLER_MASTER.
  * E_CONTROLLER_MASTER is pedantically correct within the PROS styleguide, but
  * not convienent for most student programmers.
  */
#define PROS_USE_SIMPLE_NAMES

  /**
   * If defined, C++ literals will be available for use. All literals are in the
   * pros::literals namespace.
   *
   * For instance, you can do `4_mtr = 50` to set motor 4's target velocity to 50
   */
#define PROS_USE_LITERALS

#include "api.h"

// Raider Robotics library includes
#include "lib-rr/nodes/NodeManager.h"
#include "lib-rr/nodes/actuator_nodes/MotorNode.h"
#include "lib-rr/nodes/sensor_nodes/ADIAnalogInNode.h"
#include "lib-rr/nodes/sensor_nodes/ADIDigitalInNode.h"
#include "lib-rr/nodes/sensor_nodes/ADIEncoderNode.h"
#include "lib-rr/nodes/sensor_nodes/ADIGyroNode.h"
#include "lib-rr/nodes/sensor_nodes/ADIUltrasonicNode.h"
#include "lib-rr/nodes/sensor_nodes/InertialSensorNode.h"
#include "lib-rr/nodes/sensor_nodes/ControllerNode.h"
#include "lib-rr/nodes/system_nodes/CompetitionStatusNode.h"
#include "lib-rr/nodes/system_nodes/ProsTimeNode.h"
#include "lib-rr/nodes/system_nodes/BatteryNode.h"
#include "lib-rr/nodes/sensor_nodes/InertialSensorNode.h"
#include "lib-rr/nodes/system_nodes/ConnectionCheckerNode.h"
#include "lib-rr/nodes/subsystems/IDriveNode.h"
#include "lib-rr/nodes/subsystems/IConveyorNode.h"
#include "lib-rr/nodes/subsystems/IRollerIntakeNode.h"
#include "lib-rr/auton/auton_actions/DriveStraightAction.h"
#include "lib-rr/auton/auton_actions/FollowPathAction.h"
#include "lib-rr/eigen/Eigen/Dense"
#include "lib-rr/pathing/PathManager.h"
#include "lib-rr/util/Logger.h"

// Project-specific includes
#include "nodes/auton_nodes/AutonManagerNode.h"
#include "auton/auton_actions/DeployAction.h"
#include "nodes/ClawNode.h"
#include "nodes/TankDriveNode.h"
#include "nodes/LiftNode.h"

   /**
    * You should add more #includes here
    */
    //#include "okapi/api.hpp"
    //#include "pros/api_legacy.h"

    /**
     * If you find doing pros::Motor() to be tedious and you'd prefer just to do
     * Motor, you can use the namespace with the following commented out line.
     *
     * IMPORTANT: Only the okapi or pros namespace may be used, not both
     * concurrently! The okapi namespace will export all symbols inside the pros
     * namespace.
     */
     // using namespace pros;
     // using namespace pros::literals;
     // using namespace okapi;

     /**
      * Prototypes for the competition control tasks are redefined here to ensure
      * that they can be called from user code (i.e. calling autonomous from a
      * button press in opcontrol() for testing purposes).
      */
#ifdef __cplusplus
extern "C" {
#endif
  void autonomous(void);
  void initialize(void);
  void disabled(void);
  void competition_initialize(void);
  void opcontrol(void);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
/**
 * You can add C++-only headers here
 */
 //#include <iostream>
#endif

#endif  // _PROS_MAIN_H_
