#include "hardware/watchdog.h"

#include <wizchip_conf.h>
#include <port_common.h>
#include <w5x00_spi.h>
#include <socket.h>

#include "cpu.h"

inline void reset_all()
{
  wizchip_reset();

  watchdog_enable(1, 1);
  while(1);
}
inline void reset_cpu()
{
  watchdog_enable(1, 1);
  while(1);
}
inline void reset_ethernet()
{
  wizchip_reset();
}
inline void set_watchdog(uint32_t delay_ms, uint8_t pause_on_debug)
{
  watchdog_enable(delay_ms, pause_on_debug);
}
