#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    int num;
    char *n_txt;
} ZeroToNine;

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

typedef struct
{
    int num;
    char *n_txt;
} ElevenToNineTeen;

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

typedef struct
{
    int num;
    char *n_txt;
} Tens;

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

typedef struct
{
    int num;
    char *n_txt;
} Hundreds;

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

typedef struct
{
    int class_number;
    const char *singular;
    const char *plural;
    char *out;
} Milions;

Milions mlns[] = {
    {6, "quatrilhão", "quatrilhões"},
    {5, "trilhão", "trilhões"},
    {4, "bilhão", "bilhões"},
    {3, "milhão", "milhões"},
    {2, "mil", "mil"},
    {1, "real", "reais"}};

const int CLASSES_COUNT = sizeof(mlns) / sizeof(mlns[0]);

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

void translate_value_to_txt(int v_index, int c_index, char *value, const char *m_class)
{
    char out[512] = "";
    int l_val = atoi(value);

    if (l_val == 0)
    {
        return; // ignora grupos com 000
    }

    int hundreds = l_val / 100;
    int tens = (l_val % 100) / 10;
    int unities = l_val % 10;

    // Centena
    if (hundreds > 0)
    {
        if (l_val % 100 == 0 && hundreds == 1)
        {
            strcat(out, "cem");
        } else if (l_val % 100 != 0 && hundreds == 1)
        {
            strcat(out, "cento");
        }
        else
        {
            strcat(out, hds[hundreds - 1].n_txt);
        }
    }

    // Espaço e "e"
    if (hundreds > 0 && (tens > 0 || unities > 0))
    {
        strcat(out, " e ");
    }

    // Dezena + Unidade
    if (tens == 1 && unities > 0)
    {
        // Exceções 11–19
        int teen = l_val % 100;
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

    // Espaço + classe
    strcat(out, " ");
    strcat(out, m_class);
    strcat(out, " ");

    printf("%s", out);
}

void identify_value_class(SplitInGroupsOfThree sigot)
{
    for (int i = sigot.group_index - 1; i >= 0; i--)
    {
        int m_class_pos = i + 1;
        int i_groups = atoi(sigot.groups[i]);

        if (i_groups == 0)
            continue;

        for (int j = 0; j < CLASSES_COUNT; j++)
        {
            if (mlns[j].class_number == m_class_pos)
            {
                const char *m_class = (i_groups == 1) ? mlns[j].singular : mlns[j].plural;
                translate_value_to_txt(i, j, sigot.groups[i], m_class);
                break;
            }
        }
    }

    printf("\n");
}

int main()
{
    MoneySplit split = money_splt_in_two_halfs("1099,99");

    SplitInGroupsOfThree sigot = split_in_groups_of_three(split.l_half);

    if (sigot.len > 0)
        identify_value_class(sigot);

    return 0;
}
