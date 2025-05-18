#include <stdio.h>
#include <string.h>

typedef struct
{
    char l_half[50];
    char r_half[50];
} MoneySplit;

typedef struct
{
    char split[50];
    char lpsit_a[50];
} ThreeSplitLeftHalfMoney;

MoneySplit money_splt_in_two_halfs(char *money) // recebe o valor "5432178,99"
{
    MoneySplit data;
    char *separator = strchr(money, ','); // identifica o separador retornando ",99"

    if (separator != NULL)
    {
        int char_amount = separator - money;      // retorna a quantidade de caracteres que vem antes da virgula/ponto
        strncpy(data.l_half, money, char_amount); // copia para dentro de "l_half" o valor "5432178" que vem antes da virgula
        data.l_half[char_amount] = '\0';          // adiciona ao final do array de strings o caracter '\0' para indicar o fim da string
        strcpy(data.r_half, separator + 1);       // copia para dentro de "r_half" o valor "99" que vem depois da virgula
    }
    else
    {
        strcpy(data.l_half, money); // Se não tiver separador copia o valor de "money" para dentro de "l_half"
        strcpy(data.r_half, "00");  // Se não tiver separador adiciona o valor "00" depois da virgula
    }

    return data;
}

void split_in_groups_of_three(char *data)
{
    int len = strlen(data); // Descobre quantos caracteres tem na string
    char groups[10][4];     // Até 10 grupos de 3 dígitos (com espaço para \0)
    int group_index = 0;    // Contador de quantos grupos já salvei

    int i = len; // Começamos do fim da string
    while (i > 0)
    {
        int start = i - 3; // Marca o início do grupo (3 posições antes) 5 432 178
        if (start < 0)
            start = 0; // Se passar do início da string, ajusta

        int size = i - start;                             // Quantos caracteres o grupo vai ter (1, 2 ou 3)
        strncpy(groups[group_index], &data[start], size); // Copia o trecho do grupo
        groups[group_index][size] = '\0';                 // Termina a string com \0

        group_index++; // Próximo grupo
        i -= 3;        // Anda 3 casas para a esquerda
    }

    // Agora os grupos estão de trás pra frente, vamos imprimir na ordem certa
    printf("Grupos de 3 digitos:\n");
    for (int j = group_index - 1; j >= 0; j--)
    {
        printf("[%s] ", groups[j]);
    }
    printf("\n");
}

int main()
{
    MoneySplit split = money_splt_in_two_halfs("5432178,99");
    split_in_groups_of_three(split.l_half);
    return 0;
}
