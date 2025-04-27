#include "philo.h"

char *skip_spaces(char *num)
{
    while (*num && (*num == ' ' || *num == '\t'))
        num++;
    return (num);
}

int char_is_space (char c)
{
    return (c == ' ' || c=='\t');
}
int string_is_all_digit(char * num)
{

    num = skip_spaces(num);
    if (*num == '-' || *num =='+')
        num++;
    while (*num && ft_isdigit(*num))
    {
        num++;
        if(char_is_space(*num))
            skip_spaces(num);
    }
    if (*num == 0)
        return (1);
    return (0);
}

int parser_check(int ac , char **av)
{
    int i;

    i = 1;
    if (ac > 6)
        return (0);
    while (i < ac)
    {
        if (!string_is_all_digit(av[i++]))
            return (0);
    }
    return (1);
}