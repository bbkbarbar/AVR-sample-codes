#include <util\delay.h>
#include "ATmega8_servo_control_real_with_pwm.c"


int main(void) {

	initServoControl();

	//setServoPosition(SERVO_LEFT);	
	//setServoPosition(SERVO_MID);	
	setServoPosition(SERVO_RIGHT);	

	for (;;) {
		_delay_ms(100);
	}

	return 0;
}
