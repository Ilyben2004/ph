#include "philo.h"

void * ft_monitor_die(void *philos)
{

    int i;
    t_private_philo * philo = (t_private_philo *) philos;
    while (1)
    {
        i = 0;
        while (i < philo->public_philo->total_philo)
        {
            if((philo + i)->started && get_time_between_2_times((philo + i)->last_meal) > philo->public_philo->time_die)
            {
                printf("get_time_between_2_times((philo + i)->last_meal) = %ld > philo->public_philo->time_die = %ld\n",get_time_between_2_times((philo + i)->last_meal) , philo->public_philo->time_die);
                print_passed_time_in_ms(philo->public_philo->start_time , "monitor " , -1);
                printf("philo[%d] is dead last_mael %ld started = %d\n",i + 1 , get_time_between_2_times((philo + i)->last_meal) , (philo + i)->started);
                exit(0);
            }
            i++;
        }

    }
}

void * ft_monitor_eat(void *philos)
{

    int i;
    int all_eat;
    t_private_philo * philo = (t_private_philo *) philos;
    while (1)
    {
        i = 0;
        all_eat =1;
        while (all_eat && i < philo->public_philo->total_philo)
        {
            if((philo + i)->started == 0 || (philo + i)->count_eat < philo->public_philo->how_many_eats)
                all_eat = 0;
            i++;
        }
        if (all_eat)
            exit(0);

    }
}