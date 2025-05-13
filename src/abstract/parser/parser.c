#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include "parser.h"

PARSED_DATA_T parsing_buffor[PARSER_COUNT];

typedef uint8_t bool;
#define complited 0
#define error 1
#define data parsing_buffor[parser_num]

bool split_command(uint8_t parser_num);
bool arguments_to_int(uint8_t parser_num, char** cstrs);
char** create_cstr_from_arguments(uint8_t parser_num, char** cstrs);

PARSED_DATA_T* parse_at_command(char* command, const uint8_t parser_num)
{
  if(PARSER_COUNT > parser_num)
  {
    data.err = 0;

    data.command_ptr = command;
    if(split_command(parser_num))     
    {
      data.err = 1;
      return &data;
    }
    char* split_buffor[15];
    create_cstr_from_arguments(parser_num, split_buffor);
    if(arguments_to_int(parser_num, split_buffor))
    {
      data.err = 1;
      return &data;
    }
    
    return &data;
  }
  data.err = 1;
  return &data;
}
bool split_command(uint8_t parser_num)
{
  char* delimiter = strchr(data.command_ptr, '=');
  if(delimiter == NULL)     return error;

  *delimiter = '\0';
strcpy(data.function, data.command_ptr); strcpy(data.other, delimiter + 1);
  return complited;
}
inline bool compare_functions(uint8_t parser_num, char* function)
{
  return !strcmp(data.function, function);
}
inline char** create_cstr_from_arguments(uint8_t parser_num, char** cstrs)
{
  uint8_t counter = 1;
  cstrs[0] = data.other;
  for(uint8_t i = 0; data.other[i] != '\0'; i++)
  {
    if(data.other[i] == ',')    
    {
      data.other[i] = '\0';

      cstrs[counter++] = &data.other[i + 1];     
    }
  }
  cstrs[counter] = NULL;

  return cstrs;
}
bool arguments_to_int(uint8_t parser_num, char** cstrs)
{
  int result = 0;
  uint8_t counter = 0;
  for(uint8_t i = 0; cstrs[i] != NULL; i++)
  {
    for(uint8_t j = 0; cstrs[i][j] != '\0'; j++)
    {
      if(cstrs[i][j] < '0' || cstrs[i][j] > '9')    return error;
    }

    result = atoi(cstrs[i]);
    if(result < 0 || result > 255)    return error;
    data.arguments[counter++] = result; 
  }
  data.arguments_count = counter;

  return complited;
}
