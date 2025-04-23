#ifndef PHILO_H
#define PHILO_H
#include <stdio.h>
#include <pthread.h>

typedef struct s_public_philo
{
    int philo_nums;
    int t_die;
    int t_sleep;
    int t_eat;

} t_public_philo;

typedef struct s_private_philo
{
    int id;
    int count_eat;
    pthread_mutex_t     mutex;
} t_private_philo;

#endif