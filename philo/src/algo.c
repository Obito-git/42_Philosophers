#include "../philo.h"
void	take_left_fork(t_settings *s)
{
	int			left;

	left = s->philo->id;
	if (!s->philo->left && s->forks[left]->isfree)
	{
		s->forks[left]->isfree = FALSE;
		s->philo->left = s->forks[left];
		printf("%d Fork %d was taken by %d\n", (int) (get_current_time_ms()
		- *s->ms_from_start), left, s->philo->id);
	}
}

void	take_rigth_fork(t_settings *s)
{
	int			right;

	right = s->philo->id - 1;
	if (right < 0)
		right = s->number_of_philo - 1;
	if (!s->philo->rigth && s->forks[right]->isfree)
	{
		s->forks[right]->isfree = FALSE;
		s->philo->rigth = s->forks[right];
		printf("%d Fork %d was taken by %d\n", (int) (get_current_time_ms()
		- *s->ms_from_start), right, s->philo->id);
	}
}

t_bool	take_fork(t_settings *s)
{
	if (s->philo->id % 2 == 0)
	{
		take_rigth_fork(s);
		take_left_fork(s);
	}
	else
	{
		take_left_fork(s);
		take_rigth_fork(s);
	}
	return (s->philo->left && s->philo->rigth);
}

void set_philo_deathtime(t_settings *s, long start)
{
	s->philo->time_to_death -= (int) (get_current_time_ms() - start);
	if (*s->are_alive && s->philo->time_to_death <= 0)
	{
		printf("%ld %d died\n", get_current_time_ms() - *s->ms_from_start,
				 s->philo->id);
		*s->are_alive = 0;
	}
}

//TODO sleep and eat t_boll for and call are_alive from calling function
t_bool	go_sleep(t_settings *s)
{
	long	start_sleeping;

	start_sleeping = get_current_time_ms();
	if (*s->are_alive)
	{
		printf("%d %d is sleeping\n", (int) (start_sleeping
			- *s->ms_from_start), s->philo->id);
		while (*s->are_alive && get_current_time_ms() - start_sleeping < s->time_to_sleep)
		{
			usleep(1);
			if (get_current_time_ms() - start_sleeping > s->philo->time_to_death)
				return (FALSE);
		}
		set_philo_deathtime(s, start_sleeping);
	}
	printf("%d %d is thinking\n", (int) (get_current_time_ms()
		- *s->ms_from_start), s->philo->id);
	return (TRUE);
}

t_bool	go_eat_and_sleep(t_settings *s)
{
	long	start_eating;

	if (*s->are_alive)
	{
		s->philo->time_to_death = s->time_to_die;
		start_eating = get_current_time_ms();
		printf("%d %d is eating\n", (int) (start_eating
			- *s->ms_from_start), s->philo->id);
		while (*s->are_alive && get_current_time_ms() - start_eating < s->time_to_eat)
		{
			usleep(1);
			if (get_current_time_ms() - start_eating > s->philo->time_to_death)
				return (FALSE);
		}
		s->philo->left->isfree = TRUE;
		s->philo->rigth->isfree = TRUE;
		s->philo->left = NULL;
		s->philo->rigth = NULL;
		set_philo_deathtime(s, start_eating);
	}
	return (go_sleep(s));
}


void	*routine(void *arg)
{
	//TODO USLEEP INTAGRATION IN LOOPS FOR OPTIMISATION
	t_settings	*s;
	long			think_start;
	pthread_mutex_t	mutex;

	//pthread_mutex_init(&mutex, NULL);
	if (pthread_mutex_init(&mutex, NULL) != 0)
        printf("\n mutex init failed\n");

	s = (t_settings *) arg;

	while (*s->are_alive)
	{
		pthread_mutex_lock(&mutex);
		think_start = get_current_time_ms();
		usleep(1);
		take_fork(s);
		set_philo_deathtime(s, think_start);
		pthread_mutex_unlock(&mutex);

		if (*s->are_alive && s->philo->left && s->philo->rigth)
			go_eat_and_sleep(s);
	}
	pthread_mutex_destroy(&mutex);

	return (NULL);
}
