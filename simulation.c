#include "philo.h"

static void ft_mutex_lock(pthread_mutex_t *left, pthread_mutex_t *right, int id)
{
    if (id % 2 == 1)
    {
        pthread_mutex_lock(left);
        pthread_mutex_lock(right);
    }
    else
    {
        pthread_mutex_lock(right);
        pthread_mutex_lock(left);
    }
}

static void ft_mutex_unlock(pthread_mutex_t *left, pthread_mutex_t *right, int id)
{
    if (id % 2 == 1)
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

static void *ft_eat(void *called_philo)
{

    t_private_philo *philo = (t_private_philo *)called_philo;

    int called_id = philo->id;
    ft_mutex_lock(&philo->left_fork, &philo->right_fork, called_id);
    usleep(philo->public_philo->time_eat * 1000);
    philo->count_eat = philo->count_eat + 1;
    print_passed_time_in_ms(philo->public_philo->start_time, "eating :", called_id);
    ft_mutex_unlock(&philo->left_fork , &philo->right_fork , called_id );
    return (NULL);
}

static void *ft_think(void *called_philos)
{
    t_private_philo *philo = (t_private_philo *)called_philos;

    int called_id = philo->id;
    print_passed_time_in_ms(philo->public_philo->start_time, "thinking : ", called_id);
    return (NULL);
}

static void *ft_sleep(void *philos)
{
    t_private_philo *philo = (t_private_philo *)philos;

    int called_id = philo->id;
    usleep(philo->public_philo->time_sleep * 1000);
    print_passed_time_in_ms(philo->public_philo->start_time, "sleeping : ", called_id);
    return (NULL);
}

void *philo_sim(void *called_philo)
{
    while (1)
    {
        ft_eat(called_philo);
        ft_sleep(called_philo);
        ft_think(called_philo);
    }
    return (NULL);
}