/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibennaje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:24:04 by ibennaje          #+#    #+#             */
/*   Updated: 2025/05/14 20:24:05 by ibennaje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	helper_func(t_private_philo *p, void (sim_func(void *)))
{
	int	execute;

	pthread_mutex_lock(p->public_philo->dead_lock);
	execute = !p->public_philo->end_sim;
	pthread_mutex_unlock(p->public_philo->dead_lock);
	if (execute)
		return (sim_func((void *)p), 0);
	return (1);
}

void	*philo_sim(void *called_philo)
{
	t_private_philo	*p;
	int				condition;

	p = (t_private_philo *)called_philo;
	if (p->id % 2 == 1)
		usleep((p->public_philo->time_eat * 1000) / 2);
	while (1)
	{
		pthread_mutex_lock(p->eat_lock);
		condition = (p->public_philo->optional_arg == 0)
			|| (p->count_eat < p->public_philo->how_many_eats);
		if (condition == 0)
		{
			pthread_mutex_unlock(p->eat_lock);
			return (NULL);
		}
		pthread_mutex_unlock(p->eat_lock);
		if (helper_func(called_philo, ft_eat) || helper_func(called_philo,
				ft_sleep) || helper_func(called_philo, ft_think))
			break ;
		if (p->id % 2 == 1)
			usleep(500);
	}
	return (NULL);
}
