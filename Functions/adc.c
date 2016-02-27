
/*==========================================================================*
 *							 							   					*
 *			 	ADC (10bit) (tested in channel 0 and channel 5)			   	*
 *							 Tested on ATmega8			   					*
 *							 							   					*
 *		  DDRC seems doesn't matter (it works when DDRC = 0b11101111)		*
 *							 							   					*
 *							 							   					*
 *							 Boor Andras - 2014			   					*
 *							 							   					*
 *==========================================================================*/

void initADC() {
    //         76543210
    ADMUX  = 0b01000000;
    ADCSRA = 0b10000111;
} 


uint16_t readADC(uint8_t ch) {

    ADMUX = (ADMUX & 0b11110000) | ch;
//  01000001    ADMUX jelenlegi állapota (1-es ADC csatorna beállítva)
//& 11110000    ezzel toroljuk az elozo portok kivalasztast
//= 01000000    eredmenynek kapjuk az eredeti ADMUX beallitast
//| 00000101    "rairjuk" az ADC csatornat
//= 01000101    
    ADCSRA|=(1<<ADSC);          // konverzió elindítás
    while(ADCSRA & (1<<ADSC));  // várás az átalakításra
    return (ADCL | (ADCH<<8));  // adc érték visszaadása

}



// =========================================================================================
//									Other ADC-related methods
// =========================================================================================


/*
float getDivisionValue(float adc){

	if(adc >= 1016){
		return 73.1;
	}else
	if(adc >= 1000){
		return 74.07;
	}
	else
	if(adc >= 963){
		return 74.08;
	}
	else
	if(adc >= 934){
		return 74.72;
	}
	else
	if(adc >= 902){
		return 75.17;
	}
	else
	if(adc >= 863){
		return 75.04;
	}
	else
	if(adc >= 829){
		return 75.36;
	}
	else
	if(adc >= 794){
		return 75.62;
	}
	else
	if(adc >= 760){
		return 76.00;
	}
	else
	if(adc >= 724){
		return 76.13;
	}
	else
	if(adc >= 690){
		return 76.67;
	}
	else
	if(adc >= 653){
		return 76.82;
	}
	else
	if(adc >= 620){
		return 77.40;
	}
	else
	if(adc >= 584){
		return 77.87;
	}
	else
	if(adc >= 549){
		return 78.43;
	}
	else
	if(adc >= 519){
		return 79.85;
	}

	return 80.0;

}
*/

float getVoltage(uint16_t adcVal){
	
	//float retVal = ((adcVal / getDivisionValue(adcVal)) / 0.90);	// Divide with 0.91 (0.90-0.92) because of the new state of voltage divider potmeter.

	float retVal = (((adcVal/70.38)-9.9)*1.11)+9.9;

	return retVal;

}
