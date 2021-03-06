#pragma config(Hubs,  S1, MatrxRbtcs, none,     none,     none)
#pragma config(Hubs,  S2, MatrxRbtcs, none,     none,     none)
#pragma config(Sensor, S3,     BumpBottomLift, sensorTouch)
#pragma config(Motor,  motorA,          Intake_Left,   tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorB,          Intake_Right,  tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_Matrix_S1_1, LiftRight,     tmotorMatrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_Matrix_S1_2, Right_Back,    tmotorMatrix, openLoop, encoder)
#pragma config(Motor,  mtr_Matrix_S1_3, Right_Front,   tmotorMatrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_Matrix_S1_4, Conveyor,      tmotorMatrix, openLoop, encoder)
#pragma config(Motor,  mtr_Matrix_S2_1, LiftLeft,      tmotorMatrix, openLoop, encoder)
#pragma config(Motor,  mtr_Matrix_S2_2, Spindle,       tmotorMatrix, openLoop, encoder)
#pragma config(Motor,  mtr_Matrix_S2_3, Left_Back,     tmotorMatrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_Matrix_S2_4, Left_Front,    tmotorMatrix, openLoop, encoder)
#pragma config(Servo,  srvo_Matrix_S1_1, BoxDoor,              tServoStandard)
#pragma config(Servo,  srvo_Matrix_S1_2, servo2,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_3, BoxArm,               tServoStandard)
#pragma config(Servo,  srvo_Matrix_S1_4, servo4,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S2_1, servo5,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S2_2, SecondaryHolder,      tServoStandard)
#pragma config(Servo,  srvo_Matrix_S2_3, servo7,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S2_4, Holder,               tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// Lift Control
int liftRightEncoder = 0;
bool liftAtTarget = false;
int liftJoystickDeadzone = 10;
int liftTargets[5] = {0, 2500, 7600, 12650, 9800};
int currentLiftTarget = liftTargets[0];
int acceptableLiftError = 25;

/*
 * Move lift towards target position
 * Returns whether or not the lift is currently at the correct position
 */
bool updateLift()
{
  liftRightEncoder = nMotorEncoder[LiftRight];

	int rightLiftError = currentLiftTarget - nMotorEncoder[LiftRight];

	rightLiftError = abs(rightLiftError) > acceptableLiftError ? rightLiftError : 0;

	if(rightLiftError < 0)
	{
		motor[LiftLeft] = -100;
		motor[LiftRight] = -100;
	}
	else if(rightLiftError > 0)
	{
		motor[LiftLeft] = 100;
		motor[LiftRight] = 100;
	}

	liftAtTarget = (rightLiftError == 0);

	// Return true if left and right error are both within the acceptable range
	return liftAtTarget;
}

void liftAtSpeed(float speed)
{
	motor[LiftLeft] = speed;
	motor[LiftRight] = speed;
}

void liftForTime(float time, int speed)
{
	ClearTimer(T1);

	while(time1[T1] < time * 1000)
	{
		motor[LiftLeft] = speed;
		motor[LiftRight] = speed;
	}

	motor[LiftLeft] = 0;
	motor[LiftRight] = 0;
}

void zeroLiftEncoders()
{
	nMotorEncoder[LiftLeft] = 0;
	nMotorEncoder[LiftRight] = 0;
}
