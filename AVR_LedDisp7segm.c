//==============================================================================================================
//======================================== LED_DISP_7_SEGM.C BEGIN =============================================
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

char numToChar(unsigned char num){

	return ('0' + (num % 10));

}


unsigned char showChar(char c, char withDot){

	A(0);
	B(0);
	C(0);
	D(0);
	E(0);
	F(0);
	G(0);
	P(0);

	unsigned char retVal = 1;

	switch(c){
		case ' ':
			A(0);
			B(0);
			C(0);
			D(0);
			E(0);
			F(0);
			G(0);
			break;/**/		
		case 'S':
		case 's':
		case '5':
			A(1);
			B(0);
			C(1);
			D(1);
			E(0);
			F(1);
			G(1);
			break;
		case 'Z':
		case 'z':
		case '2':
			A(1);
			B(1);
			C(0);
			D(1);
			E(1);
			F(0);
			G(1);
			break;/*
		case 'E':
		case 'e':
			A(1);
			B(0);
			C(0);
			D(1);
			E(1);
			F(1);
			G(1);
			break;/*
		case 'L':
			A(0);
			B(0);
			C(0);
			D(1);
			E(1);
			F(1);
			G(0);
			break;
		case 'l':
			A(0);
			B(0);
			C(0);
			D(1);
			E(1);
			F(0);
			G(0);
			break;
		case 'I':
			A(0);
			B(0);
			C(0);
			D(0);
			E(1);
			F(1);
			G(0);
			break;
		case 'i':
			A(0);
			B(0);
			C(0);
			D(0);
			E(1);
			F(0);
			G(0);
			break;
		case 'D':
		case 'd':
			A(0);
			B(1);
			C(1);
			D(1);
			E(1);
			F(0);
			G(1);
			break;/**/
		case 'G':
		case 'g':
		case '6':
			A(1);
			B(0);
			C(1);
			D(1);
			E(1);
			F(1);
			G(1);
			break;
		case '-':
			A(0);
			B(0);
			C(0);
			D(0);
			E(0);
			F(0);
			G(1);
			break;
		/*case '_':
			A(0);
			B(0);
			C(0);
			D(1);
			E(0);
			F(0);
			G(0);
			break;*/
		case '.':
			A(0);
			B(0);
			C(0);
			D(0);
			E(0);
			F(0);
			G(0);
			P(1);
			break;	/**/
		case '0':
			A(1);
			B(1);
			C(1);
			D(1);
			E(1);
			F(1);
			G(0);
			break;
		case '1':
		case 'I':
			A(0);
			B(1);
			C(1);
			D(0);
			E(0);
			F(0);
			G(0);
			break;
		case '3':
			A(1);
			B(1);
			C(1);
			D(1);
			E(0);
			F(0);
			G(1);
			break;
		case '4':
			A(0);
			B(1);
			C(1);
			D(0);
			E(0);
			F(1);
			G(1);
			break;
		case '7':
			A(1);
			B(1);
			C(1);
			D(0);
			E(0);
			F(0);
			G(0);
			break;
		case '8':
			A(1);
			B(1);
			C(1);
			D(1);
			E(1);
			F(1);
			G(1);
			break;
		case '9':
			A(1);
			B(1);
			C(1);
			D(0);
			E(0);
			F(1);
			G(1);
			break;/*
		case 'A':
		case 'a':
			A(1);
			B(1);
			C(1);
			D(0);
			E(1);
			F(1);
			G(1);
			break;
		case 'B':
		case 'b':
			A(0);
			B(0);
			C(1);
			D(1);
			E(1);
			F(1);
			G(1);
			break;
		case 'C':
			A(1);
			B(0);
			C(0);
			D(1);
			E(1);
			F(1);
			G(1);
			break;
		case 'c':
			A(0);
			B(0);
			C(0);
			D(1);
			E(1);
			F(0);
			G(1);
			break;
		case 'F':
		case 'f':
			A(1);
			B(0);
			C(0);
			D(0);
			E(1);
			F(1);
			G(1);
			break;
		case 'T':
		case 't':
			A(0);
			B(0);
			C(0);
			D(1);
			E(1);
			F(1);
			G(1);
			break;
		case 'O':
			A(1);
			B(1);
			C(1);
			D(1);
			E(1);
			F(1);
			G(0);
			break;/**/
		case 'o':
			A(0);
			B(0);
			C(1);
			D(1);
			E(1);
			F(0);
			G(1);
			break;
		case 'H':
			A(0);
			B(1);
			C(1);
			D(0);
			E(1);
			F(1);
			G(1);
			break;/*
		case 'h':
			A(0);
			B(0);
			C(1);
			D(0);
			E(1);
			F(1);
			G(1);
			break;
		/*case '?':
			A(1);
			B(1);
			C(1);
			D(0);
			E(0);
			F(1);
			G(0);
			P(1);
			break;/**/
		case 'P':
		case 'p':
			A(1);
			B(1);
			C(0);
			D(0);
			E(1);
			F(1);
			G(1);
			break;/*
		case '>':
			A(0);
			B(0);
			C(0);
			D(0);
			E(1);
			F(1);
			G(1);
			break;
		case '<':
			A(0);
			B(1);
			C(1);
			D(0);
			E(0);
			F(0);
			G(1);
			break;
		/*case '[':
		case '(':
		case '{':
			A(1);
			B(0);
			C(0);
			D(1);
			E(1);
			F(1);
			G(0);
			break;
		case ']':
		case ')':
		case '}':
			A(1);
			B(1);
			C(1);
			D(1);
			E(0);
			F(0);
			G(0);
			break;/**//*
		case '=':
			A(0);
			B(0);
			C(0);
			D(1);
			E(0);
			F(0);
			G(1);
			break;
		/*case '°':
			A(1);
			B(1);
			C(0);
			D(0);
			E(0);
			F(1);
			G(1);
			break;	/**/
		default:
			A(1);
			B(0);
			C(0);
			D(1);
			E(0);
			F(0);
			G(1);
			retVal = 0;
			break;

	}	//eof switch

	if(withDot > 0){
		P(1);
	}else
	if(withDot < 0){
		P(0);
	}
	/**/
	return retVal;

}	// eof func < unsigned char void showChar(char c, char withDot) >



/*
 * 	float val; 			> 	In
 *	char result[6];		>	Out
 */
void getTextToShow(float val, char* result){
	char* buffer;
	buffer = (char*)calloc(sizeof(char), 4);
	int l;
	l = sprintf(buffer, "%.3f", val);

	//printf("L: %d\n", l);
	//printf("|%s|\n", buffer);

	//char result[6];
	int i=0;
	for(i; i<5; i++){
		result[i] = buffer[i];
	}
}


void getDisplayContentFromValue(float value, T_CharToShow displayContent[4] ){

	T_CharToShow NA;
	NA.c = 'n';
	NA.withDot = -1;

	unsigned char i;
	for(i=0;i<4;i++){
		displayContent[i] = NA;
	}

	if(value >= 10000){
		displayContent[0].c = 'H';
		displayContent[1].c = 'I';
		displayContent[2].c = 'G';
		displayContent[3].c = 'H';
		displayContent[0].withDot = 1;
		displayContent[1].withDot = 1;
		displayContent[2].withDot = 1;
		displayContent[3].withDot = 1;
		return;
	}

	displayContent[0].withDot = 0;
	displayContent[1].withDot = 0;
	displayContent[2].withDot = 0;
	displayContent[3].withDot = 0;
	/*
	char text[6] = {' ', ' ', ' ', ' ', ' ', ' '};
	getTextToShow(value, text);

	int j=0;
	for(i=0; i<5; i++)
	{	
		if(text[i+1] == '.'){
			displayContent[j].withDot = 1;
		}
		if(text[i] != '.'){
			displayContent[j].c = text[i];
			j++;
		}
	}
	/**/

}


//==============================================================================================================
//========================================= LED_DISP_7_SEGM.C END ==============================================
//==============================================================================================================