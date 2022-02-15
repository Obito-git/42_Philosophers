#include "../philo.h"

void	take_left_fork(t_settings *s, int left)
{
	if (*s->are_alive && !s->philo->left && s->forks[left]->isfree)
	{
		s->forks[left]->isfree = FALSE;
		s->philo->left = s->forks[left];
		printf("%ld %d has taken a fork\n", get_current_time_ms()
		- *s->ms_from_start, s->philo->id);
	}
}

void	take_rigth_fork(t_settings *s, int right)
{
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
	int			right;

	right = s->philo->id - 1;
	if (right < 0)
		right = s->number_of_philo - 1;
	int			left;
	left = s->philo->id;
	if (s->philo->id % 2 == 0 && s->philo->id + 1 != s->number_of_philo)
	{
		if (s->forks[left]->isfree && s->forks[right]->isfree)
		{
			take_rigth_fork(s, right);
			take_left_fork(s, left);
		}
	}
	else
	{
		if (s->forks[left]->isfree && s->forks[right]->isfree)
		{
			take_left_fork(s, left);
			take_rigth_fork(s, right);
		}
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
			printf("%ld %d is sleeping\n", start_sleeping - *s->ms_from_start, s->philo->id);
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
		printf("%ld %d is thinking\n", get_current_time_ms() - *s->ms_from_start, s->philo->id);
	pthread_mutex_unlock(s->print);
	usleep(500);
	set_philo_deathtime(s, start_sleeping);
}

void	go_eat(t_settings *s)
{
	long	start_eating;

	if (*s->are_alive)
	{
		s->philo->time_to_death = s->time_to_die;
		start_eating = get_current_time_ms();
		if (*s->are_alive)
			printf("%ld %d is eating\n", start_eating - *s->ms_from_start, s->philo->id);
		while (*s->are_alive && get_current_time_ms() - start_eating < s->time_to_eat)
		{
			usleep(100);
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
