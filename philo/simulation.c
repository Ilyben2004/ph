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

static int	end_simulation(t_private_philo *p)
{
	int	end_sim;

	pthread_mutex_lock(p->public_philo->dead_lock);
	end_sim = p->public_philo->end_sim;
	pthread_mutex_unlock(p->public_philo->dead_lock);
	return (end_sim);
}

int	helper_func(t_private_philo *p, void (sim_func(void *)))
{
	return (sim_func((void *)p), 0);
}

void	*philo_sim(void *called_philo)
{
	t_private_philo	*p;
	int				condition;
	int				odd_w;

	p = (t_private_philo *)called_philo;
	odd_w = (p->public_philo->total_philo % 2 == 1 && p->id % 2 == 1);
	if (p->id % 2 == 1)
		usleep((p->public_philo->time_eat * 1000) / 2);
	while (p->public_philo->total_philo > 1)
	{
		pthread_mutex_lock(p->eat_lock);
		condition = (p->public_philo->optional_arg == 0)
			|| (p->count_eat < p->public_philo->how_many_eats);
		pthread_mutex_unlock(p->eat_lock);
		if (condition == 0)
			return (NULL);
		if (helper_func(called_philo, ft_eat) || helper_func(called_philo,
				ft_sleep) || helper_func(called_philo, ft_think))
			break ;
		if (odd_w)
			usleep(500);
		if (end_simulation(p))
			break ;
	}
	return (NULL);
}
