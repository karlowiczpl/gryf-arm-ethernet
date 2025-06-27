#ifndef CPU_H
#define CPU_H

#include <stdint.h>

void reset_all();
void reset_cpu();
void reset_ethernet();
void set_watchdog(uint32_t delay_ms, uint8_t pause_on_debug);

#endif // !CPU_H
