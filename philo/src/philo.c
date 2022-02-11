#include "../philo.h"

t_bool  philo_fork_init(t_philo **phils, t_fork **forks, t_settings *set)
{
    int i;

    i = 0;
    if (!phils || !forks)
        return (FALSE);
    while (i < set->number_of_philo)
    {
        phils[i] = philo_init(i, set->time_to_die);
        forks[i] = fork_init(i);
        if (!forks[i] || !phils[i])
        {
            while (i >= 0)
            {
                free(phils[i]);
                free(forks[i]);
                i--;
            }
            free(phils);
            free(forks);
            return (FALSE);
        }
        i++;
    }
    return (TRUE);
}

int main(int ac, char **av)
{
    /*
    struct timeval tv;
    while (1)
    {
        gettimeofday(&tv, NULL);
        long long milliseconds = tv.tv_sec*1000LL + tv.tv_usec/1000;
        if ((milliseconds / 1000) % 10 == 0)
        {
            printf("10 sec\n");
            sleep(2);
        }
    }
    (void) ac;
    (void) av;
    */
    t_settings  *set;
    t_philo     **philos;
    t_fork      **forks;

    if (ac != 5)
    {
        ft_printf("Wrong args count\n");
        return (1);
    }
    set = parse_args(av);
    if (!set)
        return (1);
    philos = (t_philo **) malloc(sizeof(t_philo) * set->number_of_philo);
    forks = (t_fork **) malloc(sizeof(t_fork) * set->number_of_philo);
    if (!philo_fork_init(philos, forks, set))
    {
        ft_printf("Malloc error!\n");
        free(set);
        return (1);
    }
    set_and_start_threads(philos, forks, set);
    free_forks(forks, set->number_of_philo);
    free_philos(philos, set->number_of_philo);
    free(set);
    return (0);
}
