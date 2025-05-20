#include <stdio.h>
#include <string.h>

typedef struct
{
    char l_half[50];
    char r_half[50];
} MoneySplit;

typedef struct
{
    int len;
    char groups[10][4];
    int group_index;
    int i;
} SplitInGroupsOfThree;

typedef struct
{
    int class_number;
    const char *singular;
    const char *plural;
    char *fator;
    char *out;
} MonetaryClasses;

MonetaryClasses mcs[] = {
    {6, "quatrilhão", "quatrilhões", "1000000000000000"},
    {5, "trilhão", "trilhões", "1000000000000"},
    {4, "bilhão", "bilhões", "1000000000"},
    {3, "milhão", "milhões", "1000000"},
    {2, "mil", "mil", "1000"},
    {1, "real", "reais", "1"}};

const int CLASSES_COUNT = sizeof(mcs) / sizeof(mcs[0]);

MoneySplit money_splt_in_two_halfs(char *value)
{
    MoneySplit money_split;
    char *separator = strchr(value, ',');

    if (separator != NULL)
    {
        int char_amount = separator - value;
        strncpy(money_split.l_half, value, char_amount);
        money_split.l_half[char_amount] = '\0';
        strcpy(money_split.r_half, separator + 1);
    }
    else
    {
        strcpy(money_split.l_half, value);
        strcpy(money_split.r_half, "00");
    }

    return money_split;
}

SplitInGroupsOfThree split_in_groups_of_three(char *value)
{
    SplitInGroupsOfThree sigot;
    sigot.len = strlen(value);
    sigot.group_index = 0;
    sigot.i = sigot.len;

    while (sigot.i > 0)
    {
        int start = sigot.i - 3;
        if (start < 0)
            start = 0;

        int size = sigot.i - start;
        strncpy(sigot.groups[sigot.group_index], &value[start], size);
        sigot.groups[sigot.group_index][size] = '\0';

        sigot.group_index++;
        sigot.i -= 3;
    }

    return sigot;
}

void identify_value_class(SplitInGroupsOfThree sigot)
{
    // [005] [432] [178]  → (5 milhões, 432 mil, 178 reais)

    for (int i = sigot.group_index - 1; i >= 0; i--)
    {
        int m_class_pos = i + 1;
        printf("The value of group %d is: %s\n", m_class_pos, sigot.groups[i]);

        for (int j = 0; j < CLASSES_COUNT; j++)
        {
            if (mcs[j].class_number == m_class_pos)
            {
                printf("The class of group %s is: %s\n\n", sigot.groups[i], mcs[j].singular);
                break;
            }
        }
    }
}

int main()
{
    MoneySplit split = money_splt_in_two_halfs("5432178,99");

    SplitInGroupsOfThree sigot = split_in_groups_of_three(split.l_half);

    // printf("Total monetary classes: %d\n", CLASSES_COUNT);
    printf("group_index: %d\n", sigot.group_index);

    if (sigot.len > 0)
        identify_value_class(sigot);

    return 0;
}

