#include "../unity/unity.h"
#include "../include/m2t.h"

void setUp(void) {}
void tearDown(void) {}

void test_money_split_should_split_correctly(void)
{
    MoneySplit result = money_splt_in_two_halfs("1234,56");
    TEST_ASSERT_EQUAL_STRING("1234", result.l_half);
    TEST_ASSERT_EQUAL_STRING("56", result.r_half);

    MoneySplit result2 = money_splt_in_two_halfs("1234,00");
    TEST_ASSERT_EQUAL_STRING("1234", result2.l_half);
    TEST_ASSERT_EQUAL_STRING("00", result2.r_half);

    MoneySplit result3 = money_splt_in_two_halfs("0,00");
    TEST_ASSERT_EQUAL_STRING("0", result3.l_half);
    TEST_ASSERT_EQUAL_STRING("00", result3.r_half);

    MoneySplit result4 = money_splt_in_two_halfs("0,03");
    TEST_ASSERT_EQUAL_STRING("0", result4.l_half);
    TEST_ASSERT_EQUAL_STRING("03", result4.r_half);
}

void test_money_split_without_comma_should_default_to_00(void)
{
    MoneySplit result = money_splt_in_two_halfs("789");
    TEST_ASSERT_EQUAL_STRING("789", result.l_half);
    TEST_ASSERT_EQUAL_STRING("00", result.r_half);

    MoneySplit result2 = money_splt_in_two_halfs("001");
    TEST_ASSERT_EQUAL_STRING("001", result2.l_half);
    TEST_ASSERT_EQUAL_STRING("00", result2.r_half);

    MoneySplit result3 = money_splt_in_two_halfs("01");
    TEST_ASSERT_EQUAL_STRING("01", result3.l_half);
    TEST_ASSERT_EQUAL_STRING("00", result3.r_half);

    MoneySplit result4 = money_splt_in_two_halfs("101233");
    TEST_ASSERT_EQUAL_STRING("101233", result4.l_half);
    TEST_ASSERT_EQUAL_STRING("00", result4.r_half);
}

void test_split_in_groups_of_three_should_split_7_digits(void) {
    char input[] = "1234567";
    SplitInGroupsOfThree result = split_in_groups_of_three(input);

    TEST_ASSERT_EQUAL_INT(7, result.len);
    TEST_ASSERT_EQUAL_STRING("567", result.groups[0]);
    TEST_ASSERT_EQUAL_STRING("234", result.groups[1]);
    TEST_ASSERT_EQUAL_STRING("1", result.groups[2]);
    TEST_ASSERT_EQUAL_INT(3, result.group_index);
}

void test_split_in_groups_of_three_should_split_4_digits(void) {
    char input[] = "1234";
    SplitInGroupsOfThree result = split_in_groups_of_three(input);

    TEST_ASSERT_EQUAL_INT(4, result.len);
    TEST_ASSERT_EQUAL_STRING("234", result.groups[0]);
    TEST_ASSERT_EQUAL_STRING("1", result.groups[1]);
    TEST_ASSERT_EQUAL_INT(2, result.group_index);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_money_split_should_split_correctly);
    RUN_TEST(test_money_split_without_comma_should_default_to_00);
    RUN_TEST(test_split_in_groups_of_three_should_split_7_digits);
    RUN_TEST(test_split_in_groups_of_three_should_split_4_digits);
    return UNITY_END();
}
