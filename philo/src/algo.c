#include "../philo.h"

long	get_current_time_ms(void)
{
	struct timeval tv;

    gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000);
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
			usleep(100);
			set_philo_deathtime(s, think_start);
		}
	}
	return (NULL);
}
