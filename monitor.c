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

// int all_started(t_private_philo * philos)
// {
//     int i;

//     i = 0;
//     while (i < philos->public_philo->total_philo)
//     {

//         if ()
//     }

// }

void	*ft_monitor_die(void *philos)
{
	int				i;
	int				die_condition;
	t_private_philo	*philo;
	int				started;

	i = 0;
	usleep(1000);
	philo = (t_private_philo *)philos;
	if (philo->public_philo->total_philo == 1)
	{
		pthread_mutex_lock(philo->public_philo->dead_lock);
		print_passed_time_in_ms(philo->public_philo->start_time,
			"has taken a fork", ((philo + i)->id), philo);
		usleep(philo->public_philo->time_die * 1000);
		print_passed_time_in_ms(philo->public_philo->start_time, "died ",
			((philo + i)->id), NULL);
		philo->public_philo->end_sim = 1;
		pthread_mutex_unlock(philo->public_philo->dead_lock);
		return (NULL);
	}
	while (1)
	{
		i = 0;
		while (i < philo->public_philo->total_philo)
		{
			pthread_mutex_lock((philo + i)->started_lock);
			started = (philo + i)->started;
			die_condition = get_time_between_2_times((philo
						+ i)->last_meal) >= philo->public_philo->time_die;
			pthread_mutex_unlock((philo + i)->started_lock);
			if (started && die_condition)
			{
				print_passed_time_in_ms(philo->public_philo->start_time,
					"died ", ((philo + i)->id), NULL);
				pthread_mutex_lock(philo->public_philo->dead_lock);
				philo->public_philo->end_sim = 1;
				pthread_mutex_unlock(philo->public_philo->dead_lock);
				return (NULL);
			}
			i++;
		}
		usleep(50);
		if (philo->public_philo->optional_arg == 1)
		{
			if (all_philos_ate(philo))
				return (NULL);
		}
	}
	return (philo);
}
