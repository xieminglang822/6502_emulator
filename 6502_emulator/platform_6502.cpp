#include "platform_6502.h"

/*
	Every time CPU run is called, it performs following steps:
	1. read instruction from PC location
	2. do pc++
	3. executing instruction
	4. update register information, update memory (if applicable)
*/
void cpu_6502::run()
{

};