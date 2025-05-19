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

MoneySplit money_splt_in_two_halfs(char *value) // recebe o valor "5432178,99"
{
    MoneySplit money_split;
    char *separator = strchr(value, ','); // identifica o separador retornando ",99"

    if (separator != NULL)
    {
        int char_amount = separator - value;             // retorna a quantidade de caracteres que vem antes da virgula/ponto
        strncpy(money_split.l_half, value, char_amount); // copia para dentro de "l_half" o valor "5432178" que vem antes da virgula
        money_split.l_half[char_amount] = '\0';          // adiciona ao final do array de strings o caracter '\0' para indicar o fim da string
        strcpy(money_split.r_half, separator + 1);       // copia para dentro de "r_half" o valor "99" que vem depois da virgula
    }
    else
    {
        strcpy(money_split.l_half, value); // Se não tiver separador copia o valor de "value" para dentro de "l_half"
        strcpy(money_split.r_half, "00");  // Se não tiver separador adiciona o valor "00" depois da virgula
    }

    return money_split;
}

SplitInGroupsOfThree split_in_groups_of_three(char *value)
{
    SplitInGroupsOfThree sigot;
    sigot.len = strlen(value); // Descobre quantos caracteres tem na string
    sigot.group_index = 0;    // Contador de quantos grupos já salvei
    sigot.i = sigot.len;      // Começamos do fim da string

    while (sigot.i > 0)
    {
        int start = sigot.i - 3; // Marca o início do grupo (3 posições antes) 5 432 178
        if (start < 0)
            start = 0; // Se passar do início da string, ajusta

        int size = sigot.i - start;                                   // Quantos caracteres o grupo vai ter (1, 2 ou 3)
        strncpy(sigot.groups[sigot.group_index], &value[start], size); // Copia o trecho do grupo
        sigot.groups[sigot.group_index][size] = '\0';                 // Termina a string com \0

        sigot.group_index++; // Próximo grupo
        sigot.i -= 3;        // Anda 3 casas para a esquerda
    }

    return sigot;
}

int main()
{
    MoneySplit split = money_splt_in_two_halfs("5432178,99");
    SplitInGroupsOfThree sigot = split_in_groups_of_three(split.l_half);
    printf("Grupos de 3 digitos:\n");
    for(int i = sigot.group_index - 1; i >=0; i--)
    {
        printf("[%s] ", sigot.groups[i]);
    }
    printf("\n");
    return 0;
}
