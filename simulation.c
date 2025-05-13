#include "philo.h"

void ft_usleep(long time_to_sleep_in_ms)
{
	int i;
	struct timeval start_sleep;

	i = 0;
	gettimeofday(&start_sleep, NULL);
	while (get_time_between_2_times(start_sleep) < time_to_sleep_in_ms)
		usleep(10);
}

static void ft_mutex_lock(pthread_mutex_t *left, pthread_mutex_t *right, int id,
						  t_public_philo *public_philo, t_private_philo *private_philo)
{
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

static void ft_mutex_unlock(pthread_mutex_t *left, pthread_mutex_t *right,
							int id)
{
	if (id % 2 == 0)
	{
		pthread_mutex_unlock(left);
		pthread_mutex_unlock(right);
	}
	else
	{
		pthread_mutex_unlock(right);
		pthread_mutex_unlock(left);
	}
}

void ft_eat(void *called_philo)
{
	t_private_philo *philo;
	int called_id;

	philo = (t_private_philo *)called_philo;
	called_id = philo->id;
	ft_mutex_lock(philo->left_fork, philo->right_fork, called_id,
				  philo->public_philo, philo);
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

void ft_think(void *called_philos)
{
	t_private_philo *philo;
	int called_id;

	philo = (t_private_philo *)called_philos;
	called_id = philo->id;
	print_passed_time_in_ms_protected(philo->public_philo->start_time,
									  "is thinking", called_id, philo);
}

void ft_sleep(void *philos)
{
	t_private_philo *philo;
	int called_id;

	philo = (t_private_philo *)philos;
	called_id = philo->id;
	print_passed_time_in_ms_protected(philo->public_philo->start_time,
									  "is sleeping", called_id, philo);
	ft_usleep(philo->public_philo->time_sleep);
}

int helper_func(t_private_philo *p, void(sim_func(void *)))
{
	int execute;

	pthread_mutex_lock(p->public_philo->dead_lock);
	execute = !p->public_philo->end_sim;
	pthread_mutex_unlock(p->public_philo->dead_lock);
	if (execute)
		return (sim_func((void *)p), 0);
	return (1);
}

void *philo_sim(void *called_philo)
{
	t_private_philo *p = (t_private_philo *)called_philo;
	int condition;
	if (p->id % 2 == 1)
		usleep((p->public_philo->time_eat * 1000) / 2);

	while (1)
	{
		pthread_mutex_lock(p->eat_lock);
		condition = (p->public_philo->optional_arg == 0) || (p->count_eat < p->public_philo->how_many_eats);
		if (condition == 0)
		{
			pthread_mutex_unlock(p->eat_lock);
			return (NULL);
		}
		pthread_mutex_unlock(p->eat_lock);
		if (helper_func(called_philo, ft_eat) || helper_func(called_philo, ft_sleep) || helper_func(called_philo, ft_think))
			break;
		if (p->id % 2 == 1)
			usleep(500);
	}

	return (NULL);
}