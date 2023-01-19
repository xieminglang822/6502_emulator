#pragma once
#include <cstdint>

class cpu_6502;
/*
*	Prototype class for 6502 executable instructions
*	Each instructions should contain following field:
*		-> Functionality: what does this instruction do, being presented as the run() function
*		-> Clock cycle: how many cycles this instruction will consume
*		-> Addressing mode: what kind of addressing mode is this instruction using
*		-> Opcode
*		-> Instuction length (operands)
*	Eventually all instructions will be read from ROM and fit into this class
*/
class instruction_6502
{
	friend class cpu_6502;
private:
	uint8_t _opcode;
};