#include <stdlib.h>
#include <string.h>
#include "../unity/unity.h"
#include "../include/m2t.h"

void setUp(void) {}
void tearDown(void) {}

void test_money_split_should_split_correctly(void)
{
    MoneySplit result = money_splt_in_two_halfs("1234,56");
    TEST_ASSERT_EQUAL_STRING("1234", result.left_value);
    TEST_ASSERT_EQUAL_STRING("56", result.right_value);

    MoneySplit result2 = money_splt_in_two_halfs("1234,00");
    TEST_ASSERT_EQUAL_STRING("1234", result2.left_value);
    TEST_ASSERT_EQUAL_STRING("00", result2.right_value);

    MoneySplit result3 = money_splt_in_two_halfs("0,00");
    TEST_ASSERT_EQUAL_STRING("0", result3.left_value);
    TEST_ASSERT_EQUAL_STRING("00", result3.right_value);

    MoneySplit result4 = money_splt_in_two_halfs("0,03");
    TEST_ASSERT_EQUAL_STRING("0", result4.left_value);
    TEST_ASSERT_EQUAL_STRING("03", result4.right_value);
}

void test_money_split_without_comma_should_default_to_00(void)
{
    MoneySplit result = money_splt_in_two_halfs("789");
    TEST_ASSERT_EQUAL_STRING("789", result.left_value);
    TEST_ASSERT_EQUAL_STRING("00", result.right_value);

    MoneySplit result2 = money_splt_in_two_halfs("001");
    TEST_ASSERT_EQUAL_STRING("001", result2.left_value);
    TEST_ASSERT_EQUAL_STRING("00", result2.right_value);

    MoneySplit result3 = money_splt_in_two_halfs("01");
    TEST_ASSERT_EQUAL_STRING("01", result3.left_value);
    TEST_ASSERT_EQUAL_STRING("00", result3.right_value);

    MoneySplit result4 = money_splt_in_two_halfs("101233");
    TEST_ASSERT_EQUAL_STRING("101233", result4.left_value);
    TEST_ASSERT_EQUAL_STRING("00", result4.right_value);
}

void test_split_in_groups_of_three_should_split_7_digits(void)
{
    char input[] = "1234567";
    SplitInGroupsOfThree result = split_in_groups_of_three(input);

    TEST_ASSERT_EQUAL_INT(7, result.len);
    TEST_ASSERT_EQUAL_STRING("567", result.groups[0]);
    TEST_ASSERT_EQUAL_STRING("234", result.groups[1]);
    TEST_ASSERT_EQUAL_STRING("1", result.groups[2]);
    TEST_ASSERT_EQUAL_INT(3, result.group_index);
}

void test_split_in_groups_of_three_should_split_4_digits(void)
{
    char input[] = "1234";
    SplitInGroupsOfThree result = split_in_groups_of_three(input);

    TEST_ASSERT_EQUAL_INT(4, result.len);
    TEST_ASSERT_EQUAL_STRING("234", result.groups[0]);
    TEST_ASSERT_EQUAL_STRING("1", result.groups[1]);
    TEST_ASSERT_EQUAL_INT(2, result.group_index);
}

void test_identify_value_class_should_map_correct_class_names(void)
{
    SplitInGroupsOfThree split;
    split.group_index = 3;
    strcpy(split.groups[0], "240"); // unidade: reais
    strcpy(split.groups[1], "452"); // milhar: mil
    strcpy(split.groups[2], "001"); // milhão: milhão
    split.len = 7;
    split.i = 0;

    int result_count = 0;
    ValueClassResult *results = identify_value_class(split, &result_count);

    TEST_ASSERT_EQUAL_INT(3, result_count);
    TEST_ASSERT_EQUAL_STRING("milhão", results[0].class_name);
    TEST_ASSERT_EQUAL_STRING("mil", results[1].class_name);
    TEST_ASSERT_EQUAL_STRING("reais", results[2].class_name);

    for (int i = 0; i < result_count; i++)
    {
        free(results[i].group_value_str);
    }
    free(results);
}

void test_translate_right_value_to_txt_should_return_quarenta_e_cinco_centavos(void)
{
    MoneySplit ms = {.right_value = "45"};
    char *result = translate_right_value_to_txt(ms);
    TEST_ASSERT_EQUAL_STRING(" e quarenta e cinco centavos", result);
    free(result);
}

void test_translate_right_value_to_txt_should_return_um_centavo(void)
{
    MoneySplit ms = {.right_value = "01"};
    char *result = translate_right_value_to_txt(ms);
    TEST_ASSERT_EQUAL_STRING(" e um centavo", result);
    free(result);
}

void test_translate_right_value_to_txt_should_return_vinte_centavos(void)
{
    MoneySplit ms = {.right_value = "20"};
    char *result = translate_right_value_to_txt(ms);
    TEST_ASSERT_EQUAL_STRING(" e vinte centavos", result);
    free(result);
}

void test_translate_right_value_to_txt_should_return_zero_centavos(void)
{
    MoneySplit ms = {.right_value = "00"};
    char *result = translate_right_value_to_txt(ms);
    TEST_ASSERT_EQUAL_STRING(" centavos", result); // Ainda inclui "centavos"
    free(result);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_money_split_should_split_correctly);
    RUN_TEST(test_money_split_without_comma_should_default_to_00);
    RUN_TEST(test_split_in_groups_of_three_should_split_7_digits);
    RUN_TEST(test_split_in_groups_of_three_should_split_4_digits);
    RUN_TEST(test_translate_right_value_to_txt_should_return_quarenta_e_cinco_centavos);
    RUN_TEST(test_translate_right_value_to_txt_should_return_um_centavo);
    RUN_TEST(test_translate_right_value_to_txt_should_return_vinte_centavos);
    RUN_TEST(test_translate_right_value_to_txt_should_return_zero_centavos);
    RUN_TEST(test_identify_value_class_should_map_correct_class_names);
    return UNITY_END();
}
