#include "philo.h"

void ft_eat(void *called_philo)
{
    t_called_philo *philo = (t_called_philo *)called_philo;
    t_private_philo *philos_array = philo->all_philos;
    t_public_philo *public_philo = (philos_array)->public_philo;
    int called_id = philo->called_philo->id;
    pthread_mutex_lock((philos_array + ((called_id + 1) % philos_array->public_philo->total_philo) ));
    pthread_mutex_lock(philo->called_philo);
}

void ft_think(void *called_philos)
{
    t_called_philo *philo = (t_called_philo *)called_philos;
    t_private_philo *philos_array = philo->all_philos;
    t_public_philo *public_philo = (philos_array)->public_philo;
    int called_id = philo->called_philo->id;
    printf("im philo %d thinking\n", called_id);
    print_passed_time_in_ms(philo->start_time);
}

void ft_sleep(void *philos)
{
    t_called_philo *philo = (t_called_philo *)philos;
    t_private_philo *philos_array = philo->all_philos;
    int called_id = philo->called_philo->id;
    printf("im philo %d  sleeping\n", called_id);
    print_passed_time_in_ms(philo->start_time);
    usleep(philo->all_philos->public_philo->time_sleep * 1000);
    printf("im philo %d i wokeup\n");
    print_passed_time_in_ms(philo->start_time);
}