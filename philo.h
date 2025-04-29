#ifndef PHILO_H
#define PHILO_H
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_public_philo
{
    int optional_arg;
    int total_philo;
    long time_die;
    int time_eat;
    int time_sleep;
    int how_many_eats;
    int end_sim;
    pthread_mutex_t *dead_lock;
    struct timeval start_time;

} t_public_philo;

typedef struct s_private_philo
{
    pthread_t threadid;
    int id;
    struct timeval last_meal;
    int started;
    int count_eat;
    pthread_mutex_t *eat_lock;

    t_public_philo *public_philo;
     pthread_mutex_t * started_lock ;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *left_fork;
    // pthread_mutex_t *left;11;
} t_private_philo;
 
// even left -> right
// odd right->left

// left mine
// right next

void print_passed_time_in_ms(struct timeval start_time, char *operation, int id , t_private_philo * philo );
int print_passed_time_in_ms_protected(struct timeval start_time, char *operation, int id, t_private_philo *philo);

void *philo_sim(void *called_philo);
t_private_philo *init_called_philo(t_private_philo **called_philo, int ac, char **av);
long get_time_between_2_times(struct timeval start_time);
void *ft_monitor_die(void *philos);

// parsing functions
char *skip_spaces(char *num);
int string_is_all_digit(char *num);
int parser_check(int ac, char **av);

// libft
int ft_isdigit(int c);
long ft_atoi(const char *str);

#endif