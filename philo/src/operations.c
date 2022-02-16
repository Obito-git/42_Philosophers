#include "../philo.h"

void	put_forks(t_settings *s)
{
	if (s->philo->id % 2 == 0)
	{
		s->philo->left->isfree = TRUE;
		s->philo->rigth->isfree = TRUE;
	}
	else
	{
		s->philo->rigth->isfree = TRUE;
		s->philo->left->isfree = TRUE;
	}
	s->philo->left = NULL;
	s->philo->rigth = NULL;
}

void	go_eat(t_settings *s)
{
	long	start_eating;

	if (*s->are_alive)
	{
		s->philo->time_to_death = s->time_to_die;
		start_eating = get_current_time_ms();
		if (*s->are_alive)
			printf("%ld %d is eating\n", start_eating - *s->ms_from_start, s->philo->id + 1);
		while (*s->are_alive && get_current_time_ms() - start_eating < s->time_to_eat)
		{
			usleep(100);
			if (get_current_time_ms() - start_eating > s->philo->time_to_death)
				break ;
		}
		s->philo->times_eat--;
		put_forks(s);
		set_philo_deathtime(s, start_eating);
	}
}

void	go_sleep(t_settings *s)
{
	long	start_sleeping;

	start_sleeping = get_current_time_ms();
	if (*s->are_alive)
	{
		pthread_mutex_lock(s->print);
		if (*s->are_alive)
			printf("%ld %d is sleeping\n", start_sleeping - *s->ms_from_start, s->philo->id + 1);
		pthread_mutex_unlock(s->print);
		while (*s->are_alive && get_current_time_ms() - start_sleeping < s->time_to_sleep)
		{
			usleep(100);
			if (get_current_time_ms() - start_sleeping > s->philo->time_to_death)
				break ;
		}
	}
	pthread_mutex_lock(s->print);
	if (*s->are_alive)
		printf("%ld %d is thinking\n", get_current_time_ms() - *s->ms_from_start, s->philo->id + 1);
	pthread_mutex_unlock(s->print);
	usleep(500);
	set_philo_deathtime(s, start_sleeping);
}
