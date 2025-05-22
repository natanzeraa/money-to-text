#ifndef M2T_H
#define M2T_H

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

typedef struct
{
    int num;
    char *n_txt;
} ElevenToNineTeen;

typedef struct
{
    int num;
    char *n_txt;
} Tens;

typedef struct
{
    int num;
    char *n_txt;
} Hundreds;

typedef struct
{
    int class_number;
    const char *singular;
    const char *plural;
    char *out;
} Milions;

typedef struct
{
    int group_index;
    int class_position;
    char *group_value_str;
    const char *class_name;
} ValueClassResult;

// Declarações
extern ZeroToNine ztn[];
extern ElevenToNineTeen etn[];
extern Tens tns[];
extern Hundreds hds[];
extern Milions mlns[];

MoneySplit money_splt_in_two_halfs(char *value);
SplitInGroupsOfThree split_in_groups_of_three(char *value);
char *translate_value_to_txt(const ValueClassResult *value_class);
const Milions *find_class_by_number(int class_number);
ValueClassResult *identify_value_class(SplitInGroupsOfThree split_groups, int *result_count);

#endif // M2T_H
