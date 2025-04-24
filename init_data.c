#include "philo.h"

t_public_philo *init_public_philo(t_public_philo **init_public_philo, int ac, char **av)
{
    *init_public_philo = malloc(sizeof(t_public_philo));
    if (!(*init_public_philo))
        return (NULL);
    (*init_public_philo)->total_philo = atoi(av[1]);
    (*init_public_philo)->time_die = atoi(av[2]);
    (*init_public_philo)->time_eat = atoi(av[3]);
    (*init_public_philo)->time_sleep = atoi(av[4]);
}

static void init_all_philos(t_private_philo *all_philos, t_public_philo *public_philo, int philos_size)
{
    int i;

    i = 0;
    while (i < philos_size)
    {
        (all_philos + i)->count_eat = 0;
        (all_philos + i)->id = i + 1;
        (all_philos + i)->last_meal = -1;
        (all_philos + i)->public_philo = public_philo;
        pthread_mutex_init((all_philos + i)->fork, NULL);
    }
}

t_called_philo *init_called_philo(t_called_philo **called_philo, int ac, int *av)
{
    t_public_philo *public_philo = malloc(sizeof(t_public_philo));
    if (!public_philo)
        return (NULL);
    *called_philo = malloc(sizeof(called_philo));
    if (!*called_philo)
        return (free(public_philo), NULL);
    (*called_philo)->all_philos = malloc(sizeof(t_private_philo) * public_philo->total_philo);
    if (!(*called_philo)->all_philos)
        return (free(public_philo), free(*called_philo), NULL);
    init_all_philos((*called_philo)->all_philos, public_philo, public_philo->total_philo);

}