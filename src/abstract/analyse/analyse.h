#ifndef ANALYSE_ABSTRACT_H
#define ANALYSE_ABSTRACT_H

#include <stdint.h>

#include <parser.h>

#define ANALYSER_COUNT 1

typedef enum {
  __all_is_good,
  __analyser_out_off_range = 10,
  __unable_to_find_function,
  __not_in_use_function,
  __error_while_function_exec
}ERRORS;
typedef struct
{
  ERRORS err;
}OUTPUT_PROPERTIES_T;
typedef uint8_t (*fun_ptr)(PARSED_DATA_T*);
typedef struct
{
  char* str;
  fun_ptr ptr; 
  uint8_t states_count;
  uint8_t max_range;
}MACRO_MAPPER_T;

extern MACRO_MAPPER_T* glob_mapper[ANALYSER_COUNT];
extern char* other_function_list[];

OUTPUT_PROPERTIES_T input_data(PARSED_DATA_T* data, uint8_t map_num);

#endif // !ANALYSE_ABSTRACT_H
