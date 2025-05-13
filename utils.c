#include "philo.h"

char *skip_spaces(char *num)
{
	while (*num && (*num == ' ' || *num == '\t'))
		num++;
	return (num);
}

int char_is_space(char c)
{
	return (c == ' ' || c == '\t');
}
int string_is_all_digit(char *num)
{
	num = skip_spaces(num);
	if (*num == '+')
		num++;
	if (*num == '-')
		return (-1);
	while (*num && ft_isdigit(*num))
	{
		num++;
		if (char_is_space(*num))
			skip_spaces(num);
	}
	if (*num == 0)
		return (1);
	return (0);
}

int parser_check(int ac, char **av)
{
	int i;
	int ret_value;

	i = 1;
	if (ac > 6)
		return (printf("too many args \n"), 0);
	if (ac < 5)
		return (printf("not enough args \n") , 0);
	while (i < ac)
	{
		ret_value = string_is_all_digit(av[i++]);
		if (ret_value == 0)
			return (printf("please enter numeric args\n"), 0);
		else if (ret_value == -1)
			return (printf("please enter posetiive numbers\n"), 0);
	}
	return (1);
}