//==============================================================================================================
//======================================== LED_DISP_7_SEGM.H BEGIN =============================================
//==============================================================================================================

//#include <stdio.h>

#ifndef SEGMENTS_DEFINED
	#define A(x)
	#define B(x)
	#define C(x)
	#define D(x)
	#define E(x)
	#define F(x)
	#define G(x)
	#define P(x)/**/
#endif

typedef struct{
	
	char c;
	char withDot;

}T_CharToShow;

char numToChar(unsigned char num);

unsigned char showChar(char c, char withDot);

/*
 * 	float val; 			> 	In
 *	char result[6];		>	Out
 */
void getTextToShow(float val, char* result);

void getDisplayContentFromValue(float value, T_CharToShow displayContent[4]);

//==============================================================================================================
//========================================= LED_DISP_7_SEGM.C END ==============================================
//==============================================================================================================