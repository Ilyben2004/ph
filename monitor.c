#include "philo.h"

void *ft_monitor_die(void *philos)
{
    int all_alive;

    all_alive = 1;

    int i;
    t_private_philo *philo = (t_private_philo *)philos;
    while (all_alive)
    {
        i = 0;
        pthread_mutex_lock(philo->public_philo->dead_lock);
        while (i < philo->public_philo->total_philo)
        {

            int started = (philo + i)->started;
            if (started && get_time_between_2_times((philo + i)->last_meal) >= philo->public_philo->time_die)
            {
                print_passed_time_in_ms(philo->public_philo->start_time, "chi phaylassof mat  ", (philo->id), NULL);
                philo->public_philo->end_sim = 1;
                all_alive = 0;
                break;
            }
            i++;
        }
        pthread_mutex_unlock(philo->public_philo->dead_lock);
        usleep(500);
    }
    return (philo);
}
