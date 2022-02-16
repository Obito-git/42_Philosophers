/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:46:19 by amyroshn          #+#    #+#             */
/*   Updated: 2022/02/16 12:20:52 by amyroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philo.h"

void	take_left_fork(t_settings *s, int left)
{
	if (!s->philo->left && s->forks[left]->isfree)
	{
		s->forks[left]->isfree = FALSE;
		s->philo->left = s->forks[left];
		printf_protected(s, "has taken a fork\n", get_ms()
			- *s->start, s->philo->id + 1);
	}
}

void	take_rigth_fork(t_settings *s, int right)
{
	if (!s->philo->rigth && s->forks[right]->isfree)
	{
		s->forks[right]->isfree = FALSE;
		s->philo->rigth = s->forks[right];
		printf_protected(s, "has taken a fork\n", get_ms()
			- *s->start, s->philo->id + 1);
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
	pthread_mutex_lock(s->mutex);
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
	pthread_mutex_unlock(s->mutex);
}

void	set_philo_deathtime(t_settings *s, long start, int wait_time)
{
	if (wait_time > 0)
		usleep(wait_time);
	pthread_mutex_lock(s->print);
	s->philo->time_to_death -= (get_ms() - start);
	if (*s->are_alive && s->philo->time_to_death < 0)
	{
		printf("%ld %d died\n", get_ms() - *s->start,
			s->philo->id + 1);
		*s->are_alive = 0;
	}
	pthread_mutex_unlock(s->print);
}

void	*routine(void *arg)
{
	t_settings		*s;
	long			think_start;

	s = (t_settings *) arg;
	while (s->philo->times_eat != 0)
	{
		pthread_mutex_lock(s->print);
		if (!*s->are_alive)
		{
			pthread_mutex_unlock(s->print);
			break ;
		}
		pthread_mutex_unlock(s->print);
		think_start = get_ms();
		take_fork(s);
		set_philo_deathtime(s, think_start, 0);
		think_start = get_ms();
		if (s->philo->left && s->philo->rigth)
			go_eat(s);
		else
			set_philo_deathtime(s, think_start, 10);
	}
	return (NULL);
}
