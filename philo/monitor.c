/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibennaje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:08:05 by ibennaje          #+#    #+#             */
/*   Updated: 2025/05/14 20:08:10 by ibennaje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	all_philos_ate(t_private_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->public_philo->total_philo)
	{
		pthread_mutex_lock((philos + i)->eat_lock);
		if ((philos + i)->count_eat < philos->public_philo->how_many_eats)
		{
			pthread_mutex_unlock((philos + i)->eat_lock);
			return (0);
		}
		pthread_mutex_unlock((philos + i)->eat_lock);
		i++;
	}
	return (1);
}

static int	one_philo_sim(t_private_philo *philo, int *i)
{
	*i = 0;
	if (philo->public_philo->total_philo == 1)
	{
		pthread_mutex_lock(philo->public_philo->dead_lock);
		pthread_mutex_lock(philo->left_fork);
		print_passed_time_in_ms(philo->public_philo->start_time,
			"has taken a fork", ((philo)->id), philo);
		usleep(philo->public_philo->time_die * 1000);
		print_passed_time_in_ms(philo->public_philo->start_time, "died ",
			((philo)->id), NULL);
		philo->public_philo->end_sim = 1;
		pthread_mutex_unlock(philo->public_philo->dead_lock);
		return (0);
	}
	return (1);
}

static int	verify_conditions(t_private_philo *philo, int i)
{
	int	started;
	int	die_condition;

	pthread_mutex_lock((philo + i)->started_lock);
	started = (philo + i)->started;
	die_condition = get_time_between_2_times((philo
				+ i)->last_meal) >= philo->public_philo->time_die;
	pthread_mutex_unlock((philo + i)->started_lock);
	return (started && die_condition);
}

static void	*end_sim(t_private_philo *philo, int i)
{
	pthread_mutex_lock(philo->public_philo->dead_lock);
	printf(KRED);
	print_passed_time_in_ms(philo->public_philo->start_time, "died ", ((philo
				+ i)->id), NULL);
	philo->public_philo->end_sim = 1;
	pthread_mutex_unlock(philo->public_philo->dead_lock);
	return (NULL);
}

void	*ft_monitor_die(void *philos)
{
	int				i;
	t_private_philo	*philo;

	philo = (t_private_philo *)philos;
	if (one_philo_sim(philo, &i) == 0)
		return (NULL);
	while (1)
	{
		i = -1;
		while (++i < philo->public_philo->total_philo)
		{
			if (verify_conditions(philo, i))
				return (end_sim(philo, i));
		}
		if (philo->public_philo->optional_arg == 1 && all_philos_ate(philo))
			return (NULL);
	}
	return (NULL);
}
