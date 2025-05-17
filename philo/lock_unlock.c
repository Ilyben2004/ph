/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_unlock.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibennaje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:44:39 by ibennaje          #+#    #+#             */
/*   Updated: 2025/05/14 20:44:40 by ibennaje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_mutex_lock(pthread_mutex_t *left, pthread_mutex_t *right, int id,
		t_private_philo *private_philo)
{
	t_public_philo	*public_philo;

	public_philo = private_philo->public_philo;
	if (id % 2 == 1)
	{
		pthread_mutex_lock(left);
		print_passed_time_in_ms_protected(public_philo->start_time,
			"has taken a fork", id, private_philo);
		pthread_mutex_lock(right);
		print_passed_time_in_ms_protected(public_philo->start_time,
			"has taken a fork", id, private_philo);
	}
	else
	{
		pthread_mutex_lock(right);
		print_passed_time_in_ms_protected(public_philo->start_time,
			"has taken a fork", id, private_philo);
		pthread_mutex_lock(left);
		print_passed_time_in_ms_protected(public_philo->start_time,
			"has taken a fork", id, private_philo);
	}
}

void	ft_mutex_unlock(pthread_mutex_t *left, pthread_mutex_t *right, int id)
{
	if (id % 2 == 0)
	{
		pthread_mutex_unlock(right);
		pthread_mutex_unlock(left);
	}
	else
	{
		pthread_mutex_unlock(left);
		pthread_mutex_unlock(right);
	}
}
