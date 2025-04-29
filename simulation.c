#include "philo.h"

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
    if (id % 2 == 1)
    {
        pthread_mutex_unlock(right);
        print_passed_time_in_ms_protected(public_philo->start_time, "tle9 the right fork", id, private_philo);
        pthread_mutex_unlock(left);
        print_passed_time_in_ms_protected(public_philo->start_time, "tle9 the left fork", id, private_philo);
    }
    else
    {
        pthread_mutex_unlock(left);
        print_passed_time_in_ms_protected(public_philo->start_time, "tle9 the left fork", id, private_philo);
        pthread_mutex_unlock(right);
        print_passed_time_in_ms_protected(public_philo->start_time, "tle9 the right fork", id, private_philo);
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
    print_passed_time_in_ms_protected(philo->public_philo->start_time , "tle9t dead_lock_mutex philo " , philo->id , philo );
    print_passed_time_in_ms_protected(philo->public_philo->start_time, "eating :", called_id, philo);
    usleep(philo->public_philo->time_eat * 1000);
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
    usleep(philo->public_philo->time_sleep * 1000);
}

int helper_func(t_private_philo *p , void (sim_func(void *)))
{
    int execute;

    pthread_mutex_lock(p->public_philo->dead_lock);
    execute = !p->public_philo->end_sim;
    pthread_mutex_unlock(p->public_philo->dead_lock);
    if (execute)
        return (sim_func((void*)p) , 0);
    return (1);
}

void *philo_sim(void *called_philo)
{
    t_private_philo *p = (t_private_philo *)called_philo;
    printf("philo %d enter the sim\n", p->id);
    while (p->count_eat < p->public_philo->how_many_eats)
    {
        if (helper_func(called_philo , ft_eat) || helper_func(called_philo , ft_sleep) || helper_func(called_philo , ft_think) )
            break;
    }
    return (NULL);
}