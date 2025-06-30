#ifndef EEPROM_H
#define EEPROM_H

#include <stdint.h>

#include "GryfSmart_Config.h"

#define FLASH_WRITE_START (PICO_FLASH_SIZE_BYTES - 4096)
#define FLASH_READ_START (FLASH_WRITE_START + XIP_BASE)

typedef struct
{
  uint8_t id;
  uint8_t ip[4];
  uint8_t gw[4];
  uint8_t sn[4];
  uint8_t new;
  uint8_t last[256];
}EEPROM_DATA_T;

void write_data_to_eeprom();
void read_data_from_eeprom();

const uint8_t* get_ip();
const uint8_t* get_sn();
const uint8_t* get_gw();

void set_eeprom_ethernet_configuration(uint8_t* ip, uint8_t* gw, uint8_t* sn);
void update_eeprom_network_data(uint8_t* ip, uint8_t* sn, uint8_t* gw);
void set_eeprom_id(uint8_t id);
void print_eeprom();

const EEPROM_DATA_T* get_eeprom_data();

#endif // !EEPROM_H
