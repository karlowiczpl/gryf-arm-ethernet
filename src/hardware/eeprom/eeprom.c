#include <stdint.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"

#include "hardware/flash.h"

#include "eeprom.h"

char buff[sizeof(EEPROM_DATA_T)];

EEPROM_DATA_T* eeprom_data = (EEPROM_DATA_T*)&buff;

inline void write_data_to_eeprom()
{
  vTaskSuspendAll();
  taskENTER_CRITICAL();

  flash_range_erase(FLASH_WRITE_START, 4096);
  flash_range_program(FLASH_WRITE_START, (const uint8_t*)&buff, sizeof(EEPROM_DATA_T));

  taskEXIT_CRITICAL();
  xTaskResumeAll();
}
inline void read_data_from_eeprom()
{
  memcpy(&buff, (const uint8_t*)(FLASH_READ_START), sizeof(EEPROM_DATA_T));
}
inline void set_eeprom_ethernet_configuration(uint8_t* ip, uint8_t* gw, uint8_t* sn)
{
  for(uint8_t i = 0; i < 4; i++)
  {
    if(ip[i] != eeprom_data->ip[i] || gw[i] != eeprom_data->gw[i] || sn[i] != eeprom_data->sn[i])
    {
      for(i = 0; i < 4; i++)
      {
        eeprom_data->ip[i] = ip[i];
        eeprom_data->gw[i] = gw[i];
        eeprom_data->sn[i] = sn[i];
      }

      write_data_to_eeprom();
      return;
    }
  }
}
inline void set_eeprom_id(uint8_t id)
{
  if(id != eeprom_data->id)
  {
    eeprom_data->id = id;

    write_data_to_eeprom();
  }
}
inline const EEPROM_DATA_T* get_eeprom_data()
{
  return eeprom_data;
}
