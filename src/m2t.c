#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/m2t.h"

ZeroToNine ztn[] = {
    {0, "zero"},
    {1, "um"},
    {2, "dois"},
    {3, "trës"},
    {4, "quatro"},
    {5, "cinco"},
    {6, "seis"},
    {7, "sete"},
    {8, "oito"},
    {9, "nove"},
};

ElevenToNineTeen etn[] = {
    {11, "onze"},
    {12, "doze"},
    {13, "treze"},
    {14, "quatorze"},
    {15, "quinze"},
    {16, "dezesseis"},
    {17, "dezessete"},
    {18, "dezoito"},
    {19, "dezenove"},
};

Tens tns[] = {
    {10, "dez"},
    {20, "vinte"},
    {30, "trinta"},
    {40, "quarenta"},
    {50, "cinquenta"},
    {60, "sessenta"},
    {70, "setenta"},
    {80, "oitenta"},
    {90, "noventa"},
};

Hundreds hds[] = {
    {100, "cem"},
    {200, "duzentos"},
    {300, "trezentos"},
    {400, "quatrocentos"},
    {500, "quinhentos"},
    {600, "seiscentos"},
    {700, "setecentos"},
    {800, "oitocentos"},
    {900, "novecentos"},
};

MonetaryClass mc[] = {
    {6, "quatrilhão", "quatrilhões"},
    {5, "trilhão", "trilhões"},
    {4, "bilhão", "bilhões"},
    {3, "milhão", "milhões"},
    {2, "mil", "mil"},
    {1, "real", "reais"},
    {0, "centavo", "centavos"},
};

const int CLASSES_COUNT = sizeof(mc) / sizeof(mc[0]);

MoneySplit money_splt_in_two_halfs(char *value)
{
    MoneySplit money_split;
    char *separator = strchr(value, ',');

    if (separator != NULL)
    {
        int char_amount = separator - value;
        strncpy(money_split.left_value, value, char_amount);
        money_split.left_value[char_amount] = '\0';
        strcpy(money_split.right_value, separator + 1);
    }
    else
    {
        strcpy(money_split.left_value, value);
        strcpy(money_split.right_value, "00");
    }

    return money_split;
}

SplitInGroupsOfThree split_in_groups_of_three(char *value)
{
    SplitInGroupsOfThree split_groups;
    split_groups.len = strlen(value);
    split_groups.group_index = 0;
    split_groups.i = split_groups.len;

    while (split_groups.i > 0)
    {
        int start = split_groups.i - 3;
        if (start < 0)
            start = 0;

        int size = split_groups.i - start;
        strncpy(split_groups.groups[split_groups.group_index], &value[start], size);
        split_groups.groups[split_groups.group_index][size] = '\0';

        split_groups.group_index++;
        split_groups.i -= 3;
    }

    return split_groups;
}

char *translate_left_value_to_txt(const ValueClassResult *value_class)
{
    char *out = malloc(512);
    out[0] = '\0';

    int left_value = atoi(value_class->group_value_str);

    if (left_value == 0)
    {
        return "";
    }

    int hundreds = left_value / 100;
    int tens = (left_value % 100) / 10;
    int unities = left_value % 10;

    if (hundreds > 0)
    {
        if (left_value % 100 == 0 && hundreds == 1)
        {
            strcat(out, "cem");
        }
        else if (left_value % 100 != 0 && hundreds == 1)
        {
            strcat(out, "cento");
        }
        else
        {
            strcat(out, hds[hundreds - 1].n_txt);
        }
    }

    if (hundreds > 0 && (tens > 0 || unities > 0))
    {
        strcat(out, " e ");
    }

    if (tens == 1 && unities > 0)
    {
        int teen = left_value % 100;
        strcat(out, etn[teen - 11].n_txt);
    }
    else
    {
        if (tens > 0)
        {
            strcat(out, tns[tens - 1].n_txt);
        }

        if (tens > 0 && unities > 0)
        {
            strcat(out, " e ");
        }

        if (unities > 0 && !(tens == 1))
        {
            strcat(out, ztn[unities].n_txt);
        }
    }

    strcat(out, " ");
    strcat(out, value_class->class_name);
    strcat(out, " ");

    return out;
}

char *translate_right_value_to_txt(MoneySplit ms)
{
    char *out = malloc(512);
    out[0] = '\0';

    int right_value = atoi(ms.right_value);

    if (right_value > 0)
    {
        strcat(out, " e ");

        int cent_tens = right_value / 10;
        int cent_units = right_value % 10;

        if (cent_tens == 1 && cent_units > 0)
        {
            strcat(out, etn[right_value - 11].n_txt);
        }
        else
        {
            if (cent_tens > 0)
            {
                strcat(out, tns[cent_tens - 1].n_txt);
            }

            if (cent_tens > 0 && cent_units > 0)
            {
                strcat(out, " e ");
            }

            if (cent_units > 0 && cent_tens != 1)
            {
                strcat(out, ztn[cent_units].n_txt);
            }
        }
    }

    strcat(out, " ");
    strcat(out, (right_value == 1) ? "centavo" : "centavos");

    return out;
}

const MonetaryClass *find_class_by_number(int class_number)
{
    for (int j = 0; j < CLASSES_COUNT; j++)
    {
        if (mc[j].class_number == class_number)
        {
            return &mc[j];
        }
    }
    return NULL;
}

ValueClassResult *identify_value_class(SplitInGroupsOfThree sigot, int *count)
{
    ValueClassResult *results = malloc(sizeof(ValueClassResult) * sigot.group_index);
    int result_index = 0;

    for (int i = sigot.group_index - 1; i >= 0; i--)
    {
        int m_class_pos = i + 1;
        int i_groups = atoi(sigot.groups[i]);

        if (i_groups == 0)
            continue;

        for (int j = 0; j < CLASSES_COUNT; j++)
        {
            if (mc[j].class_number == m_class_pos)
            {
                const char *m_class = (i_groups == 1) ? mc[j].singular : mc[j].plural;

                results[result_index].group_index = i;

                results[result_index].group_value_str = malloc(strlen(sigot.groups[i]) + 1);
                strcpy(results[result_index].group_value_str, sigot.groups[i]);

                results[result_index].class_name = m_class;
                result_index++;
                break;
            }
        }
    }

    *count = result_index;
    return results;
}
