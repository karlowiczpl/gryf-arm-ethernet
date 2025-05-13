#include <string.h>
#include <stdint.h>

#include "parser.h"

PARSED_DATA_T parsing_buffor[PARSER_COUNT];

void split_command(uint8_t parser_num);

PARSED_DATA_T* parse_at_command(char* command, const uint8_t parser_num)
{
  if(PARSER_COUNT > parser_num)
  {
    parsing_buffor[parser_num].command_ptr = command;
  }
  return NULL;
}
void split_command(uint8_t parser_num)
{
  
}
