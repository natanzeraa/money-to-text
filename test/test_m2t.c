#include "../unity/unity.h"
#include "../src/m2t.h"

void setUp(void) {}
void tearDown(void) {}

void test_money_split_should_split_correctly(void) {
    MoneySplit result = money_splt_in_two_halfs("1234,56");
    TEST_ASSERT_EQUAL_STRING("1234", result.l_half);
    TEST_ASSERT_EQUAL_STRING("56", result.r_half);
}

void test_money_split_without_comma_should_default_to_00(void) {
    MoneySplit result = money_splt_in_two_halfs("789");
    TEST_ASSERT_EQUAL_STRING("789", result.l_half);
    TEST_ASSERT_EQUAL_STRING("00", result.r_half);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_money_split_should_split_correctly);
    RUN_TEST(test_money_split_without_comma_should_default_to_00);
    return UNITY_END();
}
