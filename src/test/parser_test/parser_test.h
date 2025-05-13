#ifndef PASRSER_TEST_H
#define PASRSER_TEST_H

void test_split_command_should_split_correctly();
void test_split_command_should_return_error();
void test_compare_function();
void test_create_cstrs_from_arguments();
void test_arguments_to_int();
void test_parse_valid_command(void);
void test_parse_invalid_argument(void);
void test_parse_missing_equals_sign(void);
void test_parse_too_large_argument(void);

#endif // !PASRSER_TEST_H
