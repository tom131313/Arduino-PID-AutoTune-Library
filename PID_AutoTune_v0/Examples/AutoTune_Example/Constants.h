/*
 * Constants.h
 *
 *  Created on: Jan 23, 2016
 *      Author: 18elafrenz
 */


#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include "WPIlib.h"

// todo: Select one chassis
//#define TABLE_TOP_PG45775126000_26_9KET
#define ROBOT

#ifdef TABLE_TOP_PG45775126000_26_9KET
#ifdef ROBOT
#error "Two chasses defined"
#endif
#endif

#ifndef TABLE_TOP_PG45775126000_26_9KET
#ifndef ROBOT
#error "No chassis defined"
#endif
#endif

namespace XBOX
{
// declaring buttons as constants from the xbox joystick
const int DRIVER_PORT = 0;
const int A_BUTTON = 1;
const int B_BUTTON = 2;
const int X_BUTTON = 3;
const int Y_BUTTON = 4;
const int LEFT_BUMPER_BUTTON = 5;
const int RIGHT_BUMPER_BUTTON = 6;
const int BACK_BUTTON = 7;
const int START_BUTTON = 8;
const int LEFT_STICK_PRESS_BUTTON = 9;
const int RIGHT_STICK_PRESS_BUTTON = 10;
const int NODE_ID = 1;

// declaring axes as constants from joystick
const int LEFT_X_AXIS = 0;
const int LEFT_Y_AXIS = 1;
const int LEFT_TRIGGER_AXIS = 2;
const int RIGHT_TRIGGER_AXIS = 3;
const int RIGHT_X_AXIS = 4;
const int RIGHT_Y_AXIS = 5;
}

namespace LOGITECH
{
//declaring buttons as constants from the logitech joystick
const int TRIGGER = 1;
const int BUTTON_2 = 2;
const int BUTTON_3 = 3;
const int BUTTON_4 = 4;
const int BUTTON_5 = 5;
const int BUTTON_6 = 6;
const int BUTTON_7 = 7;
const int BUTTON_8 = 8;
const int BUTTON_9 = 9;
const int BUTTON_10 = 10;
const int BUTTON_11 = 11;
const int BUTTON_12 = 12;

//declaring axes as constants from the logitech joystick
const int X_AXIS = 0;
const int Y_AXIS = 1;
const int Z_AXIS = 2;
const int THROTTLE_AXIS = 3;
}

namespace CAN_PORT
{
const int POWER_DISTRIBUTION_PANEL = 0;

// TALONS
const int FRONT_LEFT = 0;
const int REAR_LEFT = 2;
const int FRONT_RIGHT = 1;
const int REAR_RIGHT = 3;
const int RAISE_SHOOTER = 4;
const int SHOOTER_LEFT_WHEEL = 5;
const int SHOOTER_RIGHT_WHEEL = 6;
const int SHOOTER_PUSH = 7;

const int LEFT_WINCH = 8;
const int RIGHT_WINCH = 9;
const int ARM_PIVOT = 10;
const int ARM_EXTEND = 11;
}

namespace DIO_PORT //0-9, expansion board 10+
{
const int LIGHT_RING = 10;
const int VERTICAL_LIMIT = 11;
const int ROBOT_SELECTOR = 13; //0 = practice, 1 = competition
}

namespace DRIVE_TRAIN
{
const float PI = 3.1415927;
const float WHEEL_CIRCUMFERENCE = 9.42477;
const float SLOW_ROTATE = .8;
const float TICKS_PER_REVOLUTION = 1000;
const float REVOLUTION_FOR_180_TURN = 6.66667;
}

namespace AUTONOMOUS
{
const float ROTATE_SPEED = 0.55;
const float AUTO_DRIVE_TIME = 3.3;

const int SHOOTER_ANGLE_UP = 0;
const int SHOOTER_ANGLE_DOWN = 5350;
const int SHOOTER_ANGLE_VISION = 2780; //x
const int SHOOTER_ANGLE_SHOOT = 1550; //x

const int SHOOTER_ANGLE_TOLERANCE = 25;

const int SHOOTER_PUSHER_REVERSE = 0;
const int SHOOTER_PUSHER_FORWARD = 160;
}

#endif /* SRC_CONSTANTS_H_ */
