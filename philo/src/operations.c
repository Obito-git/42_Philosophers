/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:55:17 by amyroshn          #+#    #+#             */
/*   Updated: 2022/02/16 12:01:31 by amyroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philo.h"

void	printf_protected(t_settings *s, char *msg, long time, int id)
{
	pthread_mutex_lock(s->print);
	if (*s->are_alive)
		printf("%ld %d %s", time, id, msg);
	pthread_mutex_unlock(s->print);
}

void	put_forks(t_settings *s)
{
	pthread_mutex_lock(s->mutex);
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
	pthread_mutex_unlock(s->mutex);
}

void	go_eat(t_settings *s)
{
	long	start_eating;

	s->philo->time_to_death = s->time_to_die;
	start_eating = get_ms();
	printf_protected(s, "is eating\n",
		start_eating - *s->start, s->philo->id + 1);
	while (get_ms() - start_eating < s->time_to_eat)
	{
		pthread_mutex_lock(s->print);
		if (!*s->are_alive)
		{
			pthread_mutex_unlock(s->print);
			break ;
		}
		pthread_mutex_unlock(s->print);
		usleep(100);
		if (get_ms() - start_eating > s->philo->time_to_death)
			break ;
	}
	if (s->philo->times_eat != -1)
		s->philo->times_eat--;
	put_forks(s);
	set_philo_deathtime(s, start_eating, 0);
	go_sleep(s);
}

void	go_sleep(t_settings *s)
{
	long	start_sleeping;

	start_sleeping = get_ms();
	printf_protected(s, "is sleeping\n",
		start_sleeping - *s->start, s->philo->id + 1);
	while (get_ms() - start_sleeping < s->time_to_sleep)
	{
		pthread_mutex_lock(s->print);
		if (!*s->are_alive)
		{
			pthread_mutex_unlock(s->print);
			break ;
		}
		pthread_mutex_unlock(s->print);
		usleep(100);
		if (get_ms() - start_sleeping > s->philo->time_to_death)
			break ;
	}
	printf_protected(s, "is thinking\n",
		get_ms() - *s->start, s->philo->id + 1);
	usleep(500);
	set_philo_deathtime(s, start_sleeping, 0);
}
