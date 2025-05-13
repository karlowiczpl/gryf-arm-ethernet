#include <stdint.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "unity.h"
#include "parser.h"

#include "parser_test.h"

typedef uint8_t bool;

extern bool split_command(uint8_t parser_num);
extern char** create_cstr_from_arguments(uint8_t parser_num, char** cstrs);
extern bool arguments_to_int(uint8_t parser_num, char** cstrs);

extern PARSED_DATA_T parsing_buffor[PARSER_COUNT];

int random_int(int min, int max) {
    return rand() % (max - min + 1) + min;
}
char* generate_random_string(int min_len, int max_len) {
  static const char charset[] =
      "abcdefghijklmnopqrstuvwxyz"
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
      "!@#$%^&*()_+-[]{}|;':.<>?";

  int charset_size = sizeof(charset) - 1;
  int length = min_len + rand() % (max_len - min_len + 1);

  char* result = malloc(length + 1);
  if (!result) return NULL;

  for (int i = 0; i < length; i++) {
    result[i] = charset[rand() % charset_size];
  }
  result[length] = '\0';
  return result;
}
void test_split_command_should_split_correctly() 
{
  for(int i = 0; i < 300; i++)
  {
    for(int k = 0; k < 2; k++)
    {
      char* str1 = generate_random_string(1, 15);
      char* str2 = generate_random_string(1, 15);

      char buffor[50];
      sprintf(buffor, "%s=%s", str1, str2);

      parsing_buffor[k].command_ptr = buffor;
      TEST_ASSERT_EQUAL_INT(split_command(k), 0);

      TEST_ASSERT_EQUAL_STRING(parsing_buffor[k].function, str1);
      TEST_ASSERT_EQUAL_STRING(parsing_buffor[k].other, str2);
    }
  }
}
void test_split_command_should_return_error()
{
  for(int i = 0; i < 300; i++)
  {
    for(int k = 0; k < 2; k++)
    {
      char* str1 = generate_random_string(1, 15);
      char* str2 = generate_random_string(1, 15);

      char buffor[50];
      sprintf(buffor, "%s%s", str1, str2);

      parsing_buffor[k].command_ptr = buffor;
      TEST_ASSERT_EQUAL_INT(split_command(k), 1);
    }
  }
}
void test_compare_function()
{
  for(int i = 0; i < 300; i++)
  {
    for(int k = 0; k < 2; k++)
    {
      char* str1 = generate_random_string(1, 15);
      char* str2 = generate_random_string(1, 15);

      char buffor[50];
      sprintf(buffor, "%s=%s", str1, str2);

      parsing_buffor[k].command_ptr = buffor;

      split_command(k);

      TEST_ASSERT_EQUAL_INT(compare_functions(k, str1), 1);
      TEST_ASSERT_EQUAL_INT(compare_functions(k, str2), 0);
    }
  }
}
void test_create_cstrs_from_arguments()
{
  char argument_buffor[150];
  char* buffor[10];
  char* out_buffor[50];

  for(int j = 0; j < 300; j++)
  {
    for(int k = 0; k < 2; k++)
    {
      argument_buffor[0] = '\0';

      for(int i = 0; i < 5; i++)
      {
        buffor[i] = generate_random_string(0, 5);
        strcat(argument_buffor, buffor[i]);
        if (i < 4) strcat(argument_buffor, ",");
      } buffor[5] = NULL;

      strcpy(parsing_buffor[k].other, argument_buffor);
      create_cstr_from_arguments(k, out_buffor);

      for(int i = 0; i < 6; i++)
      {
        TEST_ASSERT_EQUAL_STRING(buffor[i], out_buffor[i]);
      }

      TEST_ASSERT_EQUAL_INT(arguments_to_int(k, buffor), 1);
    }
  }
}
void test_arguments_to_int()
{
  char argument_buffor[150];
  uint8_t buffor[10];
  char* buff[50];

  for(int j = 0; j < 300; j++)
  {
    for(int k = 0; k < 2; k++)
    {
      argument_buffor[0] = '\0';

      for(int i = 0; i < 5; i++)
      {
        char num_buff[5];
        int rand_int = random_int(0, 254);
        sprintf(num_buff, "%d", rand_int);

        buffor[i] = rand_int;
        strcat(argument_buffor, num_buff);
        if (i < 4) strcat(argument_buffor, ",");
      }
      buffor[5] = 0;

      strcpy(parsing_buffor[k].other, argument_buffor);
      create_cstr_from_arguments(k, buff);

      TEST_ASSERT_EQUAL_INT(arguments_to_int(k, buff), 0);

      for(int i = 0; i < 6; i++)
      {
        TEST_ASSERT_EQUAL_INT(buffor[i], parsing_buffor[k].arguments[i]);
      }
    }
  }
  for(int j = 0; j < 300; j++)
  {
    for(int k = 0; k < 2; k++)
    {
      argument_buffor[0] = '\0';

      for(int i = 0; i < 5; i++)
      {
        char num_buff[5];
        int rand_int = random_int(255, 1000);
        sprintf(num_buff, "%d", rand_int);

        buffor[i] = rand_int;
        strcat(argument_buffor, num_buff);
        if (i < 4) strcat(argument_buffor, ",");
      }
      buffor[5] = 0;

      strcpy(parsing_buffor[k].other, argument_buffor);
      create_cstr_from_arguments(k, buff);

      TEST_ASSERT_EQUAL_INT(arguments_to_int(k, buff), 1);
    }
  }
}
void test_parse_valid_command(void) {
    char command[] = "CMD=10,20,30";
    PARSED_DATA_T* result = parse_at_command(command, 0);

    TEST_ASSERT_EQUAL_UINT8(0, result->err);
    TEST_ASSERT_EQUAL_STRING("CMD", result->function);
    TEST_ASSERT_EQUAL_UINT8(3, result->arguments_count);
    TEST_ASSERT_EQUAL_UINT8(10, result->arguments[0]);
    TEST_ASSERT_EQUAL_UINT8(20, result->arguments[1]);
    TEST_ASSERT_EQUAL_UINT8(30, result->arguments[2]);
}

void test_parse_invalid_argument(void) {
    char command[] = "CMD=10,X,30";
    PARSED_DATA_T* result = parse_at_command(command, 0);

    TEST_ASSERT_EQUAL_UINT8(1, result->err);
}

void test_parse_missing_equals_sign(void) {
    char command[] = "CMD10,20";
    PARSED_DATA_T* result = parse_at_command(command, 0);

    TEST_ASSERT_EQUAL_UINT8(1, result->err);
}

void test_parse_too_large_argument(void) {
    char command[] = "CMD=300";  // przekracza 255
    PARSED_DATA_T* result = parse_at_command(command, 0);

    TEST_ASSERT_EQUAL_UINT8(1, result->err);
}
