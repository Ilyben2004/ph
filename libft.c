#include "philo.h"

int	ft_isdigit(int c)
{
	return ((c >= '0' && c <= '9'));
}

long	ft_atoi(const char *str)
{
	int		sign;
	size_t	result;

	result = 0;
	sign = 1;
	while (*str && (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
			|| *str == '\f' || *str == '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}
