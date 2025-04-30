#include "philo.h"

void ft_usleep(long time_to_sleep_in_ms)
{
    int i = 0;
    struct timeval start_sleep;
    gettimeofday(&start_sleep , NULL);
    while (get_time_between_2_times(start_sleep) < time_to_sleep_in_ms)
        usleep(10);
}

static void ft_mutex_lock(pthread_mutex_t *left, pthread_mutex_t *right, int id, t_public_philo *public_philo, t_private_philo *private_philo)
{
    if (id % 2 == 1)
    {
        pthread_mutex_lock(left);
        print_passed_time_in_ms_protected(public_philo->start_time, "took the left fork", id, private_philo);
        pthread_mutex_lock(right);
        print_passed_time_in_ms_protected(public_philo->start_time, "took the right fork", id, private_philo);
    }
    else
    {
        pthread_mutex_lock(right);
        print_passed_time_in_ms_protected(public_philo->start_time, "took the right fork", id, private_philo);
        pthread_mutex_lock(left);
        print_passed_time_in_ms_protected(public_philo->start_time, "took the left fork", id, private_philo);
    }
}

static void ft_mutex_unlock(pthread_mutex_t *left, pthread_mutex_t *right, int id, t_public_philo *public_philo, t_private_philo *private_philo)
{
    if (id % 2 == 0)
    {
        pthread_mutex_unlock(left);
        print_passed_time_in_ms_protected(public_philo->start_time, "tle9 the left fork", id, private_philo);
        pthread_mutex_unlock(right);
        print_passed_time_in_ms_protected(public_philo->start_time, "tle9 the right fork", id, private_philo);
    }
    else
    {
        pthread_mutex_unlock(right);
        print_passed_time_in_ms_protected(public_philo->start_time, "tle9 the right fork", id, private_philo);
        pthread_mutex_unlock(left);
        print_passed_time_in_ms_protected(public_philo->start_time, "tle9 the left fork", id, private_philo);
    }
}

void ft_eat(void *called_philo)
{

    t_private_philo *philo = (t_private_philo *)called_philo;

    int called_id = philo->id;
    ft_mutex_lock(philo->left_fork, philo->right_fork, called_id, philo->public_philo, philo);
    pthread_mutex_lock(philo->public_philo->dead_lock);
    gettimeofday(&philo->last_meal, NULL);
    if (philo->started == 0)
        philo->started = 1;
    pthread_mutex_unlock(philo->public_philo->dead_lock);
    print_passed_time_in_ms_protected(philo->public_philo->start_time, "tle9t dead_lock_mutex philo ", philo->id, philo);
    print_passed_time_in_ms_protected(philo->public_philo->start_time, "eating :", called_id, philo);
    ft_usleep(philo->public_philo->time_eat);
    philo->count_eat = philo->count_eat + 1; // to lock
    ft_mutex_unlock(philo->left_fork, philo->right_fork, called_id, philo->public_philo, philo);
}

void ft_think(void *called_philos)
{
    t_private_philo *philo = (t_private_philo *)called_philos;

    int called_id = philo->id;
    print_passed_time_in_ms_protected(philo->public_philo->start_time, "thinking : ", called_id, philo);
}

void ft_sleep(void *philos)
{
    t_private_philo *philo = (t_private_philo *)philos;

    int called_id = philo->id;
    print_passed_time_in_ms_protected(philo->public_philo->start_time, "sleeping : ", called_id, philo);
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
    if (p->id % 2 == 1)
        usleep(1000);
    while ((p->public_philo->optional_arg == 0) || (p->count_eat < p->public_philo->how_many_eats))
    {
        if (helper_func(called_philo, ft_eat) || helper_func(called_philo, ft_sleep) || helper_func(called_philo, ft_think))
            break;
            if (p->id % 2 == 1)
            usleep(300);
    }
    return (NULL);
}