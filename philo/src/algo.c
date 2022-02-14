#include "../philo.h"
void	take_left_fork(t_settings *s)
{
	int			left;

	left = s->philo->id;
	if (*s->are_alive && !s->philo->left && s->forks[left]->isfree)
	{
		s->forks[left]->isfree = FALSE;
		s->philo->left = s->forks[left];
		printf("%ld %d has taken a fork\n", get_current_time_ms()
		- *s->ms_from_start, s->philo->id);
	}
}

void	take_rigth_fork(t_settings *s)
{
	int			right;

	right = s->philo->id - 1;
	if (right < 0)
		right = s->number_of_philo - 1;
	if (*s->are_alive && !s->philo->rigth && s->forks[right]->isfree)
	{
		s->forks[right]->isfree = FALSE;
		s->philo->rigth = s->forks[right];
		printf("%ld %d has taken a fork\n", get_current_time_ms()
		- *s->ms_from_start, s->philo->id);
	}
}

void	take_fork(t_settings *s)
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
}

void set_philo_deathtime(t_settings *s, long start)
{
	pthread_mutex_lock(s->death);
	if (*s->are_alive)
	{
		s->philo->time_to_death -= (get_current_time_ms() - start);
		if (*s->are_alive && s->philo->time_to_death < 0)
		{
			printf("%ld %d died\n", get_current_time_ms() - *s->ms_from_start,
					 s->philo->id);
			*s->are_alive = 0;
		}
	}
	pthread_mutex_unlock(s->death);
}

//TODO sleep and eat t_boll for and call are_alive from calling function
void	go_sleep(t_settings *s)
{
	long	start_sleeping;

	start_sleeping = get_current_time_ms();
	if (*s->are_alive)
	{
		pthread_mutex_lock(s->print);
		printf("%ld %d is sleeping\n", start_sleeping - *s->ms_from_start, s->philo->id);
		pthread_mutex_unlock(s->print);
		while (*s->are_alive && get_current_time_ms() - start_sleeping < s->time_to_sleep)
		{
			usleep(1);
			if (get_current_time_ms() - start_sleeping > s->philo->time_to_death)
				break ;
		}
		set_philo_deathtime(s, start_sleeping);
	}
	if (*s->are_alive)
	{
		pthread_mutex_lock(s->print);
		printf("%ld %d is thinking\n", get_current_time_ms() - *s->ms_from_start, s->philo->id);
		pthread_mutex_unlock(s->print);
	}
}

void	go_eat(t_settings *s)
{
	long	start_eating;

	if (*s->are_alive)
	{
		s->philo->time_to_death = s->time_to_die;
		start_eating = get_current_time_ms();
		pthread_mutex_lock(s->print);
		printf("%ld %d is eating\n", start_eating - *s->ms_from_start, s->philo->id);
		pthread_mutex_unlock(s->print);
		while (*s->are_alive && get_current_time_ms() - start_eating < s->time_to_eat)
		{
			usleep(1);
			if (get_current_time_ms() - start_eating > s->philo->time_to_death)
				break ;
		}
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
		set_philo_deathtime(s, start_eating);
	}
}

void	*routine(void *arg)
{
	t_settings		*s;
	long			think_start;

	s = (t_settings *) arg;
	while (*s->are_alive)
	{
		think_start = get_current_time_ms();
		pthread_mutex_lock(s->mutex);
		take_fork(s);
		pthread_mutex_unlock(s->mutex);
		set_philo_deathtime(s, think_start);
		think_start = get_current_time_ms();
		if (*s->are_alive && s->philo->left && s->philo->rigth)
		{
			go_eat(s);
			go_sleep(s);
		}
		else
		{
			usleep(1);
			set_philo_deathtime(s, think_start);
		}
	}
	return (NULL);
}
