#include "philo.h"

//*debugging functions
void print_public_philo(t_public_philo *public_philo)
{
    printf("************* public philo ***********\n");
    printf("public_philo->time_die = %ld \n", public_philo->time_die);
    printf("public_philo->time_eat = %d \n", public_philo->time_eat);
    printf("public_philo->time_sleep = %d\n", public_philo->time_sleep);
    printf("public_philo->total_phil= %d\n", public_philo->total_philo);
    printf("*********************************************\n");
}
void print_private_philo(t_private_philo *private_philo)
{
    printf("************* privte _ philo ***********\n");
    printf("private_philo->id = %d \n", private_philo->id);
    printf("private_philo->count_eat = %d \n", private_philo->count_eat);
    printf("*********************************************\n");
}
void test_data(t_private_philo *called_philo)
{
    t_public_philo *public_philo = (t_public_philo *)called_philo->public_philo;
    t_private_philo *all_philos = called_philo;
    int i = public_philo->total_philo;
    int j = 0;
    print_public_philo(public_philo);
    while (j < i)
    {
        print_private_philo(all_philos + j);
        j++;
    }
}

//

int main(int ac, char **av)
{
    t_private_philo *called_philo;

    if (parser_check(ac, av) == 0)
        return (printf("args error\n"), 1);
    if (!init_called_philo(&called_philo, ac, av))
        return (0);
    test_data(called_philo);
    int num_philos = called_philo->public_philo->total_philo;
    pthread_t thread_id[num_philos];
    int i = 0;
    while (i < num_philos)
    {
        pthread_create(&thread_id[i], NULL, philo_sim, called_philo + i);
        i++;
    }

    pthread_t monitor;
    pthread_t monitor_eat;
    pthread_create(&monitor, NULL, ft_monitor_die, called_philo);
    i = 0;
    while (i < num_philos)
    {
        pthread_join(thread_id[i], NULL);
        i++;
    }
    pthread_join(monitor, NULL);
}