#include <stdio.h>
#include "clock_6502.h"
#include "platform_6502.h"

int main()
{
	clock_6502 sys_clock;
	cpu_6502	nes_cpu;
	sys_clock.init(&nes_cpu);
	nes_cpu.init(&sys_clock);
	while (1)
	{
		sys_clock.run();
	}
}