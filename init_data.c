#include "philo.h"

t_public_philo *init_public_philo(t_public_philo **init_public_philo, int ac, char **av)
{
    *init_public_philo = malloc(sizeof(t_public_philo));
    if (!(*init_public_philo))
        return (NULL);
    (void)ac;
    (*init_public_philo)->total_philo = atoi(av[1]);
    (*init_public_philo)->time_die = atoi(av[2]);
    (*init_public_philo)->time_eat = atoi(av[3]);
    (*init_public_philo)->time_sleep = atoi(av[4]);
    (*init_public_philo)->how_many_eats = atoi(av[5]);
    return (*init_public_philo);
}

static void init_all_philos(t_private_philo *all_philos, t_public_philo *public_philo, int philos_size)
{
    int i;

    i = 0;
    while (i < philos_size)
    {
        // (all_philos + i)->public_philo[i].time_die;
        (all_philos + i)->started = 0;
        (all_philos + i)->count_eat = 0;
        (all_philos + i)->id = i + 1;
        (all_philos + i)->public_philo = public_philo;
        (all_philos + i)->left_fork = malloc(sizeof( pthread_mutex_t));
        pthread_mutex_init((all_philos + i)->left_fork, NULL);
        i++;
    }
    i = 0;
    while (i < philos_size)
    {
        // total 5
        //  I = 0 ->  philo[0]->right_fork = (philo + 2 % 5)
        (all_philos + i)->right_fork = (all_philos + ((i + 1) % all_philos->public_philo->total_philo))->left_fork;
        i++;
    }
}

t_private_philo *init_called_philo(t_private_philo **called_philo, int ac, char **av)
{
    t_public_philo *public_philo;

    (void)ac;
    (void)av;
    if (!init_public_philo(&public_philo, ac, av))
        return (NULL);
    gettimeofday(&(public_philo)->start_time, NULL);
    printf("public_philo->total_philo = %d\n", public_philo->total_philo);
    printf("public_philo->total_philo = %d\n", public_philo->total_philo);

    (*called_philo) = malloc(sizeof(t_private_philo) * public_philo->total_philo);
    if (!(*called_philo))
        return (free(public_philo), NULL);
    init_all_philos((*called_philo), public_philo, public_philo->total_philo);
    return (*called_philo);
}