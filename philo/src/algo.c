#include "../philo.h"
long	get_current_time_ms(void)
{
	struct timeval tv;

    gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000);
}

void	take_left_fork(t_settings *s, int left)
{
	if (*s->are_alive && !s->philo->left && s->forks[left]->isfree)
	{
		s->forks[left]->isfree = FALSE;
		s->philo->left = s->forks[left];
		printf("%ld %d has taken a fork\n", get_current_time_ms()
		- *s->ms_from_start, s->philo->id + 1);
	}
}

void	take_rigth_fork(t_settings *s, int right)
{

	if (*s->are_alive && !s->philo->rigth && s->forks[right]->isfree)
	{
		s->forks[right]->isfree = FALSE;
		s->philo->rigth = s->forks[right];
		printf("%ld %d has taken a fork\n", get_current_time_ms()
		- *s->ms_from_start, s->philo->id + 1);
	}
}

void	take_fork(t_settings *s)
{
	int			right;
	int			left;

	right = s->philo->id - 1;
	if (right < 0)
		right = s->number_of_philo - 1;
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

void set_philo_deathtime(t_settings *s, long start)
{
	pthread_mutex_lock(s->print);
	if (*s->are_alive)
	{
		s->philo->time_to_death -= (get_current_time_ms() - start);
		if (*s->are_alive && s->philo->time_to_death < 0)
		{
			printf("%ld %d died\n", get_current_time_ms() - *s->ms_from_start,
					 s->philo->id + 1);
			*s->are_alive = 0;
		}
	}
	pthread_mutex_unlock(s->print);
}

void	*routine(void *arg)
{
	t_settings		*s;
	long			think_start;

	s = (t_settings *) arg;
	while (*s->are_alive && s->philo->times_eat != 0)
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
			usleep(10);
			set_philo_deathtime(s, think_start);
		}
	}
	return (NULL);
}
