#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/m2t.h"

int main()
{
    MoneySplit split = money_splt_in_two_halfs("45240,45");

    if (atoi(split.left_value) == 0 && atoi(split.right_value) == 0)
        printf("Nenhum valor foi fornecido\n");

    SplitInGroupsOfThree split_groups = split_in_groups_of_three(split.left_value);

    int result_count;
    ValueClassResult *results = identify_value_class(split_groups, &result_count);

    for (int i = 0; i < result_count; i++)
    {
        char *real = translate_left_value_to_txt(&results[i]);
        printf("%s", real);
        free(real);
    }

    for (int i = 0; i < 1; i++)
    {
        char *cents = translate_right_value_to_txt(split);
        printf("%s", cents);
        free(cents);
    }

    printf("\n");
    free(results);

    return 0;
}