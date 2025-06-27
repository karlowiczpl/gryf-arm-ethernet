#include <stdint.h>
#include <unity.h>

#include "parser_test/parser_test.h"
#include "analyse.h"
#include "parser.h"

void setUp()    {}
void tearDown()   {}

uint8_t sample_function(PARSED_DATA_T* data)
{
  printf("test\n");
}

MACRO_MAPPER_T mapper[] = {
  {"print", sample_function},
  {"", sample_function},
};

int main(void)
{
  UNITY_BEGIN();

  RUN_TEST(test_split_command_should_split_correctly);
  RUN_TEST(test_split_command_should_return_error);
  RUN_TEST(test_compare_function);
  RUN_TEST(test_create_cstrs_from_arguments);
  RUN_TEST(test_arguments_to_int);
  RUN_TEST(test_parse_valid_command);
  RUN_TEST(test_parse_invalid_argument);
  RUN_TEST(test_parse_missing_equals_sign);
  RUN_TEST(test_parse_too_large_argument);

  return UNITY_END();

  char command[] = "print=1,1,2,3,1,4";
  PARSED_DATA_T* parsed = parse_at_command(command, 0);

  include_mapper(mapper);
  analyse_data(parsed);

}
