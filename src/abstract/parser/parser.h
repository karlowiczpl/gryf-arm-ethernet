#ifndef PARSER_ABSTRACT_H
#define PARSER_ABSTRACT_H

#include <stdint.h>

#define PARSER_COUNT 1

typedef struct
{
  char* command_ptr;
  char function[20];
  char other[50];
  uint8_t arguments[15];
  uint8_t arguments_count;
  uint8_t err;
}PARSED_DATA_T;

PARSED_DATA_T* parse_at_command(char* command, const uint8_t parser_num);
uint8_t compare_functions(uint8_t parser_num, char* function);

#endif // !PARSER_ABSTRACT_H
