/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibennaje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:05:55 by ibennaje          #+#    #+#             */
/*   Updated: 2025/05/14 20:06:02 by ibennaje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_passed_time_in_ms(struct timeval start_time, char *operation,
		int id, t_private_philo *philo)
{
	struct timeval	end_time;
	long			seconds;
	long			microseconds;
	long			total_milliseconds;
	int				execute;

	gettimeofday(&end_time, NULL);
	seconds = end_time.tv_sec - start_time.tv_sec;
	microseconds = end_time.tv_usec - start_time.tv_usec;
	total_milliseconds = (seconds * 1000) + (microseconds / 1000);
	if (philo)
	{
		pthread_mutex_lock(philo->public_philo->dead_lock);
		execute = !philo->public_philo->end_sim;
		pthread_mutex_unlock(philo->public_philo->dead_lock);
		if (execute)
			printf("%ld %d %s\n", total_milliseconds, id, operation);
	}
	else
		printf("%ld %d %s\n", total_milliseconds, id, operation);
}

long	get_time_between_2_times(struct timeval start_time)
{
	struct timeval	end_time;
	long			seconds;
	long			microseconds;
	long			total_milliseconds;

	gettimeofday(&end_time, NULL);
	seconds = end_time.tv_sec - start_time.tv_sec;
	microseconds = end_time.tv_usec - start_time.tv_usec;
	total_milliseconds = (seconds * 1000) + (microseconds / 1000);
	return (total_milliseconds);
}
