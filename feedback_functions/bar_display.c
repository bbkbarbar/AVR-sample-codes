/*
 * Returns an 8 bit value what can be shown in a ledbar (e.g.: PORTD).
 */
unsigned char getValueToShow(float val, int max){
    #define BAR_SIZE  8
                       //    142      255  
    float divVal = (max+1) / BAR_SIZE;  // 255 -> 32
    float barLength = val / divVal;     // 4,43

    uint8_t res;
    if( barLength < 0.5 ){
        res = 0b0;
    }else
    if( barLength < 1.5 ){
        res = 0b1;
    }else
    if( barLength < 2.5 ){
        res = 0b11;
    }else
    if( barLength < 3.5 ){
        res = 0b111;
    }else
    if( barLength < 4.5 ){
        res = 0b1111;       
    }else
    if( barLength < 5.5 ){
        res = 0b11111;
    }else
    if( barLength < 6.5 ){
        res = 0b111111;
    }else
    if( barLength < 7.5 ){
        res = 0b1111111;
    }else{
        res = 0b11111111;
    }

    return res;
}