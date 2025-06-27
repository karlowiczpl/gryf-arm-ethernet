#ifndef EEPROM_H
#define EEPROM_H

#include <stdint.h>

#define FLASH_WRITE_START (PICO_FLASH_SIZE_BYTES - 4096)
#define FLASH_READ_START (FLASH_WRITE_START + XIP_BASE)

typedef struct
{
  uint8_t id;
  uint8_t ip[4];
  uint8_t gw[4];
  uint8_t sn[4];
}EEPROM_DATA_T;

void write_data_to_eeprom();
void read_data_from_eeprom();

inline void set_eeprom_ethernet_configuration(uint8_t* ip, uint8_t* gw, uint8_t* sn);
inline void set_eeprom_id(uint8_t id);

inline const EEPROM_DATA_T* get_eeprom_data();

#endif // !EEPROM_H
