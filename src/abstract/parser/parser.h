#ifndef PARSER_ABSTRACT_H
#define PARSER_ABSTRACT_H

#include <stdint.h>

#define PARSER_COUNT 1

typedef struct
{
  char* command_ptr;
  char function[20];
  char other[30];
  uint8_t states[15];
}PARSED_DATA_T;

PARSED_DATA_T* parse_at_command(char* command, const uint8_t parser_num);

#endif // !PARSER_ABSTRACT_H
