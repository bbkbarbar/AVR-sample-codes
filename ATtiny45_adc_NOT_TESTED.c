// MCU: ATTiny45
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

 
#define PIN_OUT       PB2
#define PIN_IN        PB4

#define OutON         PORTB |=  (1<<PIN_OUT)
#define OutOFF        PORTB &= ~(1<<PIN_OUT)

#define	InputPIN      2


volatile unsigned short pot,i;

//-------------------------------------
unsigned short ADConvert(unsigned char channel) {
//-------------------------------------
    ADMUX &= ~(1<<MUX1|1<<MUX0);
    ADMUX |= channel;
    ADCSRA |= (1<<ADSC);
    while(ADCSRA & (1<<ADSC));
    return ADC;
//------------------------------------- 
}

// ADC Initialisierung
void ADC_Init(void) {
  
    uint16_t result;
  
    // VCC als Referenz
    ADMUX = ~(1 << REFS0);
  
    // Frequenzvorverteiler 128
    ADCSRA = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
  
    // ADC aktivieren
    ADCSRA |= (1 << ADEN);
    
    // Dummy Readout
  
    ADCSRA |= (1 << ADSC);  // eine ADC Wandlung
    while (ADCSRA & (1 << ADSC)) {;};  // auf Abschluss warten
    result = ADCW;  // Ergebnis muss einmal gelesen werden sonst wird die nächste Wandlung nicht übernommen
    
}

void init() {
//-------------------------------------
    DDRB = 0b000100;    //kimenetek
    //Init ADC
    ADC_Init();
}

int main(void) {

    init();
    OutOFF;

    while(1) {
        pot = ADConvert(2);	 
    
        if(pot < 150){
            OutON;
        }else{
            OutOFF;
        }

        _delay_ms(100);

    }//END while

}
