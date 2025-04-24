#ifndef PHILO_H
#define PHILO_H
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>



typedef struct  s_called_philo
{
    t_private_philo *called_philo;
    t_private_philo *all_philos;
    struct timeval start_time;
} t_called_philo;

typedef struct s_public_philo
{
    int total_philo;
    int time_die;
    int time_eat;
    int time_sleep;

} t_public_philo;

typedef struct s_private_philo
{
    pthread_t threadid;
    int id;
    int last_meal;
    int count_eat;
    int count_eat;
    t_public_philo *public_philo;
    pthread_mutex_t *fork;
} t_private_philo;

void print_passed_time_in_ms(struct timeval start_time);

#endif