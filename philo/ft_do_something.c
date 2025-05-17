/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_something.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibennaje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:27:17 by ibennaje          #+#    #+#             */
/*   Updated: 2025/05/14 20:27:18 by ibennaje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_usleep(long time_to_sleep_in_ms)
{
	struct timeval	start_sleep;

	gettimeofday(&start_sleep, NULL);
	while (get_time_between_2_times(start_sleep) < time_to_sleep_in_ms)
		usleep(10);
}

void	ft_eat(void *called_philo)
{
	t_private_philo	*philo;
	int				called_id;

	philo = (t_private_philo *)called_philo;
	called_id = philo->id;
	ft_mutex_lock(philo->left_fork, philo->right_fork, called_id, philo);
	pthread_mutex_lock(philo->started_lock);
	gettimeofday(&philo->last_meal, NULL);
	if (philo->started == 0)
		philo->started = 1;
	pthread_mutex_unlock(philo->started_lock);
	print_passed_time_in_ms_protected(philo->public_philo->start_time,
		"is eating", called_id, philo);
	ft_usleep(philo->public_philo->time_eat);
	pthread_mutex_lock(philo->eat_lock);
	philo->count_eat = philo->count_eat + 1;
	pthread_mutex_unlock(philo->eat_lock);
	ft_mutex_unlock(philo->left_fork, philo->right_fork, called_id);
}

void	ft_think(void *called_philos)
{
	t_private_philo	*philo;
	int				called_id;

	philo = (t_private_philo *)called_philos;
	called_id = philo->id;
	print_passed_time_in_ms_protected(philo->public_philo->start_time,
		"is thinking", called_id, philo);
}

void	ft_sleep(void *philos)
{
	t_private_philo	*philo;
	int				called_id;

	philo = (t_private_philo *)philos;
	called_id = philo->id;
	print_passed_time_in_ms_protected(philo->public_philo->start_time,
		"is sleeping", called_id, philo);
	ft_usleep(philo->public_philo->time_sleep);
}
