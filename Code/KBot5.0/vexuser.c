/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*                        Copyright (c) James Pearman                          */
/*                                   2013                                      */
/*                            All Rights Reserved                              */
/*                                                                             */
/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*    Module:     vexuser.c                                                    */
/*    Author:     James Pearman                                                */
/*    Created:    7 May 2013                                                   */
/*                                                                             */
/*    Revisions:                                                               */
/*                V1.00  XX XXX 2013 - Initial release                         */
/*                                                                             */
/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*    The author is supplying this software for use with the VEX cortex        */
/*    control system. This file can be freely distributed and teams are        */
/*    authorized to freely use this program , however, it is requested that    */
/*    improvements or additions be shared with the Vex community via the vex   */
/*    forum.  Please acknowledge the work of the authors when appropriate.     */
/*    Thanks.                                                                  */
/*                                                                             */
/*    Licensed under the Apache License, Version 2.0 (the "License");          */
/*    you may not use this file except in compliance with the License.         */
/*    You may obtain a copy of the License at                                  */
/*                                                                             */
/*      http://www.apache.org/licenses/LICENSE-2.0                             */
/*                                                                             */
/*    Unless required by applicable law or agreed to in writing, software      */
/*    distributed under the License is distributed on an "AS IS" BASIS,        */
/*    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. */
/*    See the License for the specific language governing permissions and      */
/*    limitations under the License.                                           */
/*                                                                             */
/*    The author can be contacted on the vex forums as jpearman                */
/*    or electronic mail using jbpearman_at_mac_dot_com                        */
/*    Mentor for team 8888 RoboLancers, Pasadena CA.                           */
/*                                                                             */
/*-----------------------------------------------------------------------------*/

#include <stdlib.h>

#include "ch.h"  		// needs for all ChibiOS programs
#include "hal.h" 		// hardware abstraction layer header
#include "vex.h"		// vex library header

// Digi IO configuration
static  vexDigiCfg  dConfig[kVexDigital_Num] = {
        { kVexDigital_1,    kVexSensorDigitalOutput, kVexConfigOutput,      0 },
        { kVexDigital_2,    kVexSensorDigitalOutput, kVexConfigOutput,      0 },
        { kVexDigital_3,    kVexSensorDigitalInput,  kVexConfigInput,       0 },
        { kVexDigital_4,    kVexSensorDigitalInput,  kVexConfigInput,       0 },
        { kVexDigital_5,    kVexSensorDigitalInput,  kVexConfigInput,       0 },
        { kVexDigital_6,    kVexSensorDigitalInput,  kVexConfigInput,       0 },
        { kVexDigital_7,    kVexSensorDigitalInput,  kVexConfigInput,       0 },
        { kVexDigital_8,    kVexSensorDigitalInput,  kVexConfigInput,       0 },
        { kVexDigital_9,    kVexSensorDigitalInput,  kVexConfigInput,       0 },
        { kVexDigital_10,   kVexSensorDigitalInput,  kVexConfigInput,       0 },
        { kVexDigital_11,   kVexSensorDigitalInput,  kVexConfigInput,       0 },
        { kVexDigital_12,   kVexSensorDigitalInput,  kVexConfigInput,       0 }
};

static  vexMotorCfg mConfig[kVexMotorNum] = {
        { kVexMotor_1,      kVexMotor393S,           kVexMotorReversed,       kVexSensorIME,         kImeChannel_1 },
        { kVexMotor_2,      kVexMotor393T,      	 kVexMotorNormal,       kVexSensorNone,        0 },
        { kVexMotor_3,      kVexMotor393S,       	 kVexMotorNormal,       kVexSensorNone,        0 },
        { kVexMotor_4,      kVexMotor393T,      	 kVexMotorNormal,       kVexSensorNone,        0 },
        { kVexMotor_5,      kVexMotor393T,      	 kVexMotorReversed,       kVexSensorNone,        0 },
        { kVexMotor_6,      kVexMotor393T,      	 kVexMotorNormal,       kVexSensorNone,        0 },
        { kVexMotor_7,      kVexMotor393T,      	 kVexMotorNormal,       kVexSensorNone,        0 },
        { kVexMotor_8,      kVexMotor393S,      	 kVexMotorNormal,       kVexSensorNone,        0 },
        { kVexMotor_9,      kVexMotor393T,      	 kVexMotorNormal,       kVexSensorNone,        0 },
        { kVexMotor_10,     kVexMotor393S,           kVexMotorNormal,       kVexSensorIME,         kImeChannel_2 }
};
//Motors
#define RightShooterTwo kVexMotor_1 //Integrated Motor Start
#define RightFrontBase	kVexMotor_2
#define RightShooterOne kVexMotor_3
#define LeftFrontBase	kVexMotor_4
#define Kicker			kVexMotor_5
#define Intake			kVexMotor_6
#define RightBackBase	kVexMotor_7
#define LeftShooterOne	kVexMotor_8
#define LeftBackBase	kVexMotor_9
#define LeftShooterTwo	kVexMotor_10 //Integrated Motor Finish

//Digital
#define UltrasonicOutput		kVexDigital_8 //For Intake
#define UltrasonicInput			kVexDigital_9 //For Intake
#define RightSideBreaks			kVexDigital_10
#define LeftSideBreaks			kVexDigital_11

/*-----------------------------------------------------------------------------*/
/** @brief      User setup                                                     */
/*-----------------------------------------------------------------------------*/
/** @details
 *  The digital and motor ports can (should) be configured here.
 */
void
vexUserSetup()
{
	vexDigitalConfigure( dConfig, DIG_CONFIG_SIZE( dConfig ) );
	vexMotorConfigure( mConfig, MOT_CONFIG_SIZE( mConfig ) );
}

/*-----------------------------------------------------------------------------*/
/** @brief      User initialize                                                */
/*-----------------------------------------------------------------------------*/
/** @details
 *  This function is called after all setup is complete and communication has
 *  been established with the master processor.
 *  Start other tasks and initialize user variables here
 */
void
vexUserInit()
{

}

/*-----------------------------------------------------------------------------*/
/** @brief      Autonomous                                                     */
/*-----------------------------------------------------------------------------*/
/** @details
 *  This thread is started when the autonomous period is started
 */
msg_t
vexAutonomous( void *arg )
{
    (void)arg;

    // Must call this
    vexTaskRegister("auton");

    while(1)
        {
        // Don't hog cpu
        vexSleep( 25 );
        }

    return (msg_t)0;
}



/*-----------------------------------------------------------------------------*/
/** @brief      Driver control                                                 */
/*-----------------------------------------------------------------------------*/
/** @details
 *  This thread is started when the driver control period is started
 */

msg_t
vexOperator( void *arg )
{

	(void)arg;

	// Must call this
	vexTaskRegister("operator");



	// Run until asked to terminate
	while(!chThdShouldTerminate())
		{

				// Base is Holonomic (Shooter is the front and Intake is the back)
				// Controller 1/2, Stick L/R, Axis X/Y
				int C1LX = vexControllerGet(Ch4);
				int C1LY = vexControllerGet(Ch3);
				int C1RX = vexControllerGet(Ch1);

				// Y component, X component, Rotation in that order
				vexMotorSet(LeftFrontBase, C1LY + C1LX + C1RX);
				vexMotorSet(RightFrontBase,  -C1LY + C1LX + C1RX);
				vexMotorSet(LeftBackBase,  C1LY - C1LX + C1RX);
				vexMotorSet(RightBackBase, -C1LY - C1LX + C1RX);

				// Exit condition
				if(chThdShouldTerminate()) break;

				//Shooter speeds are 85 for the color and 65 from mid-field (change if needed). I also added a full speed setting if needed also.(UPDATE: Nevermind on the full speed)
				//Right Side Shooter
				vexMotorSet(RightShooterOne, vexControllerGet( Btn6U ) * 85 + vexControllerGet( Btn6D ) * 65 );
				vexMotorSet(RightShooterTwo, vexControllerGet( Btn6U ) * 85 + vexControllerGet( Btn6D ) * 65 );
				//Left Side Shooter
				vexMotorSet(LeftShooterOne, vexControllerGet( Btn6U ) * 85 + vexControllerGet( Btn6D ) * 65);
				vexMotorSet(LeftShooterTwo, vexControllerGet( Btn6U ) * 85 + vexControllerGet( Btn6D ) * 65);

				//Intake
				vexMotorSet(Intake, vexControllerGet( Btn5U ) * 127 + vexControllerGet( Btn5D ) * -127);

				//Kicker
				vexMotorSet(Kicker, vexControllerGet( Btn7R ) * 85);

				//Breaks
				vexDigitalModeSet(RightSideBreaks, kVexDigitalOutput);
				vexDigitalModeSet(LeftSideBreaks, kVexDigitalOutput);




		// Don't hog cpu
		vexSleep( 25 );
		}

	return (msg_t)0;
}



