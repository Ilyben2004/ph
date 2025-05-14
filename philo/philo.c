/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibennaje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:45:25 by ibennaje          #+#    #+#             */
/*   Updated: 2025/05/14 20:45:28 by ibennaje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	clean_it_all(t_private_philo *private_p, pthread_t *thread_id)
{
	int				i;
	t_public_philo	*public_p;
	int				total_p;

	public_p = private_p->public_philo;
	total_p = public_p->total_philo;
	i = 0;
	free(public_p->dead_lock);
	while (i < total_p)
	{
		free((private_p + i)->left_fork);
		free((private_p + i)->eat_lock);
		free((private_p + i)->started_lock);
		i++;
	}
	free(public_p);
	free(private_p);
	free(thread_id);
	return (0);
}

//

int	main(int ac, char **av)
{
	t_private_philo	*called_philo;
	int				num_philos;
	int				i;
	pthread_t		monitor;
	pthread_t		*thread_id;

	if (parser_check(ac, av) == 0)
		return (1);
	if (!init_called_philo(&called_philo, ac, av))
		return (0);
	num_philos = called_philo->public_philo->total_philo;
	thread_id = malloc(sizeof(pthread_t) * num_philos);
	i = -1;
	gettimeofday(&called_philo->public_philo->start_time, NULL);
	while (++i < num_philos)
		pthread_create(&thread_id[i], NULL, philo_sim, called_philo + i);
	pthread_create(&monitor, NULL, ft_monitor_die, called_philo);
	i = -1;
	while (++i < num_philos)
		pthread_join(thread_id[i], NULL);
	pthread_join(monitor, NULL);
	return (clean_it_all(called_philo, thread_id));
}
