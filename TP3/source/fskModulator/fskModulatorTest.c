#include "fskModulator.h"
uint16_t* fskOut;

void App_Init (void){

	fskOut=fskModulatorInit(0);
	fskSetMsg(0b10100101);
}

void App_Run (void){
}
