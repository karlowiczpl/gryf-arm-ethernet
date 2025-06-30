#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "hardware/flash.h"

#include "eeprom.h"

EEPROM_DATA_T eeprom_data;

inline void write_data_to_eeprom()
{
  flash_range_erase(FLASH_WRITE_START, 4096);
  flash_range_program(FLASH_WRITE_START, (const uint8_t*)&eeprom_data, sizeof(EEPROM_DATA_T));
}
inline void read_data_from_eeprom()
{
  memcpy(&eeprom_data, (const uint8_t*)(FLASH_READ_START), sizeof(EEPROM_DATA_T));
}

void update_eeprom_network_data(uint8_t* ip, uint8_t* gw, uint8_t* sn)
{
  for(uint8_t i = 0; i < 4; i++)
  {
    if(ip[i] != eeprom_data.ip[i] || sn[i] != eeprom_data.sn[i] || gw[i] != eeprom_data.gw[i])
    {
      memcpy(eeprom_data.ip, ip, 4 * sizeof(uint8_t));
      memcpy(eeprom_data.gw, gw, 4 * sizeof(uint8_t));
      memcpy(eeprom_data.sn, sn, 4 * sizeof(uint8_t));

      eeprom_data.new = 1;
      write_data_to_eeprom();

      return;
    }
  }
}

inline void set_eeprom_id(uint8_t id)
{
  if(id != eeprom_data.id)
  {
    eeprom_data.id = id;

    write_data_to_eeprom();
  }
}
inline const EEPROM_DATA_T* get_eeprom_data()
{
  return &eeprom_data;
}

inline const uint8_t* get_ip()
{
  return eeprom_data.ip;
}

inline const uint8_t* get_sn()
{
  return eeprom_data.sn;
}

inline const uint8_t* get_gw()
{
  return eeprom_data.gw;
}

void print_eeprom()
{
  printf("\n\n");
  printf("id: %d\n", eeprom_data.id);
  printf("ip: %d.%d.%d.%d\n", eeprom_data.ip[0], eeprom_data.ip[1], eeprom_data.ip[2], eeprom_data.ip[3]);
  printf("gw: %d.%d.%d.%d\n", eeprom_data.gw[0], eeprom_data.gw[1], eeprom_data.gw[2], eeprom_data.gw[3]);
  printf("sn: %d.%d.%d.%d\n", eeprom_data.sn[0], eeprom_data.sn[1], eeprom_data.sn[2], eeprom_data.sn[3]);
  printf("new: %d\n", eeprom_data.new);
  printf("\n\n");
}
