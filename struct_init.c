#include "philo.h"

int	ft_atoi(const char *str)
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


t_public_philo * get_public_philo(char ** av , t_public_philo ** pu_philo)
{
    *pu_philo = malloc(sizeof(t_public_philo));
    (*pu_philo)->philo_nums = ft_atoi(av[0]);
    (*pu_philo)->t_die = ft_atoi(av[1]);
    (*pu_philo)->t_eat = ft_atoi(av[2]);
    (*pu_philo)->t_sleep = ft_atoi(av[3]);
}