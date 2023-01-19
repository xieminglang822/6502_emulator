#pragma once
#include <cstdint>
#include "instruction_6502.h"

// 6502 supports at mos t64 KB of memory via its 16 bit address bus
uint8_t memory[64 * 1024];
/* 0x0000 - 0x00FF
Referred to as "Zero Page". It is the focus of a number of special addressing modes that result in shorter (and quicker) instructions
or allow indirect access to the memory.
*/
uint8_t* const p_start_zero_page = memory;
uint8_t* const p_end_zero_page = &memory[255];

/* 0x0100 - 0x01FF
Reserved for the system stack and which cannot be relocated.
*/
uint8_t* const p_start_stack = &memory[256];
uint8_t* const p_end_stack = &memory[511];

/* 0xFFFA - 0xFFFF
Reserved bytes to store addresses
0xFFFA/B: non-maskable interrupt handler
0xFFFC/D: power on reset location
0xFFFE/F: BRK/interrupt handler
*/
uint8_t* const p_start_reserve = &memory[0xFFFA];
uint8_t* const p_end_reserve = &memory[0xFFFF];


/*
*  class definition for 6502 processor prototype
* Input interfaces:
*		-> clock tick
*		-> instructions
* Output inerfaces;
*		-> program counter (update current program counter position)
*		-> data out (if any)
* Internal members:
*		-> Registers: A, X, Y, stack, PC, status register
*		-> Memory pool: 64KB ram at most
*/
class cpu_6502
{
private:
	uint8_t* _memory_pool; // point to 64KB ram
	uint8_t	_reg_acc; // Reg A, 8 bits long accumulator.
	uint8_t	_reg_x;	// Reg X
	uint8_t	_reg_y;	// Reg X
	uint8_t	_reg_status;	// status register
	uint8_t* _p_stack;	// system stack pointer, should always be within the range of [p_start_stack, p_end_stack]

public:
	uint8_t	opcode;	// instruction opcode to be executed

};

