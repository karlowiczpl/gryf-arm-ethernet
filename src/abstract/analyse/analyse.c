#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "analyse.h"
#include "parser.h"

OUTPUT_PROPERTIES_T input_data(PARSED_DATA_T* data, uint8_t map_num)
{
  if(map_num >= ANALYSER_COUNT)   return (OUTPUT_PROPERTIES_T){.err = __analyser_out_off_range};
  if(data->err)   return (OUTPUT_PROPERTIES_T){.err = (ERRORS)(data->err)};

  for(uint8_t i = 0; glob_mapper[map_num][i].str[0] != '\0'; i++)
  {
    if(!strcpy(glob_mapper[map_num][i].str, data->function))
    {
      if(!glob_mapper[map_num][i].ptr(data))    return (OUTPUT_PROPERTIES_T){.err = __error_while_function_exec};

      return (OUTPUT_PROPERTIES_T){.err = __all_is_good};
    }
  }
  for(uint8_t i = 0; other_function_list[i][0] != '\0'; i++)
  {
    if(strcmp(other_function_list[i], data->function))
    {
      return (OUTPUT_PROPERTIES_T){.err = __not_in_use_function};
    }
  }

  return (OUTPUT_PROPERTIES_T){.err = __unable_to_find_function};
}
