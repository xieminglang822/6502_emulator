#pragma once
#include <cstdint>
#include "clock_6502.h"
#include "instruction_6502.h"

// 6502 supports at most 64 KB of memory via its 16 bit address bus
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
	memory controller for 6502 processor. The interface for other modules to access the 64KB memory, functioning as a bus arbitrator
	-> provides basic read()/write() function
	-> arbitration feature to secuer data coherency
*/
class memory_6502
{
private:
	uint8_t* _memory_pool = memory;
public:
	uint8_t	read(uint16_t addr) { return *(memory + addr); };
	uint8_t	write(uint16_t addr, uint8_t data);
};
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
	memory_6502* _memory_ctrl; // point to memory controller
	uint8_t	_reg_acc; // Reg A, 8 bits long accumulator.
	uint8_t	_reg_x;	// Reg X
	uint8_t	_reg_y;	// Reg X
	uint8_t	_reg_status;	// status register
	uint8_t* _p_stack;	// system stack pointer, should always be within the range of [p_start_stack, p_end_stack]

	clock_6502* _sys_clock;

public:
	uint8_t	opcode;	// instruction opcode to be executed
	void			init(clock_6502* clk_ptr, memory_6502* mem_ptr) { _sys_clock = clk_ptr; _memory_ctrl = mem_ptr; };
	void			run();
	uint8_t	read(uint16_t addr) {return _memory_ctrl->read(addr);};
	uint8_t	write(uint16_t addr, uint8_t data);

};

