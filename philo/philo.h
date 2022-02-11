#ifndef PHILO_H
# define PHILO_H
#include <stdio.h> //FIXME
# include <pthread.h>
# include <stdlib.h>
# include "libft/libft.h"
# include <sys/time.h>
# define TRUE 1
# define FALSE 0

typedef int     t_bool;

typedef struct s_settings
{
    int number_of_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    long    *ms_from_start;
    long          *are_alive;
    struct s_fork   **forks;
    struct s_philo  *philo;
} t_settings;

typedef struct s_fork
{
    int     id;
    t_bool  isfree;
} t_fork;


typedef struct s_philo
{
    pthread_t       thread;
    int             id;
    struct s_fork   *left;
    struct s_fork   *rigth;
    int             time_to_death;
} t_philo;

t_settings  *set_settings(int philo, int die, int eat, int sleep);
t_fork  *fork_init(int id);
t_philo *philo_init(int id, int time_to_death);
t_settings	*parse_args(char **av);
void    free_forks(t_fork **forks, int count);
void    free_philos(t_philo **philo, int count);
void	set_and_start_threads(t_philo **p, t_fork **f, t_settings *s);
void	*routine(void *arg);
long	get_current_time_ms(void);


#endif
