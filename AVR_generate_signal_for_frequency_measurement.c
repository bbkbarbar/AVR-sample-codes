
#define SEC_IN_US	  1000000

#define OUTPUT_PORT		PORTB
#define OUTPUT_PIN		  PB0

#define SIGN_COUNT		  100

/*
 * 	Generate pwm output in defined pin with 50% duty factor.
 */
void generateOutputForFrequencyMeasurement(double freqencyInHz){

	double tCycle = (1 / freqencyInHz) * SEC_IN_US;
	double tOnInUs  = tCycle * 0.5;
	double tOffInUs = tOnInUs;

	int i;
	for(i = 0; i < SIGN_COUNT; i++){

		OUTPUT_PORT |=  (1<<OUTPUT_PIN);
		_delay_us(tOnInUs);

		OUTPUT_PORT &= ~(1<<OUTPUT_PIN);
		_delay_us(tOffInUs);

	}

}

















