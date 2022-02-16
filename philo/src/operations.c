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
		start_eating = get_ms();
		if (*s->are_alive)
			printf("%ld %d is eating\n",
				start_eating - *s->start, s->philo->id + 1);
		while (*s->are_alive
			&& get_ms() - start_eating < s->time_to_eat)
		{
			usleep(100);
			if (get_ms() - start_eating > s->philo->time_to_death)
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

	start_sleeping = get_ms();
	if (*s->are_alive)
	{
		pthread_mutex_lock(s->print);
		if (*s->are_alive)
			printf("%ld %d is sleeping\n",
				start_sleeping - *s->start, s->philo->id + 1);
		pthread_mutex_unlock(s->print);
		while (*s->are_alive
			&& get_ms() - start_sleeping < s->time_to_sleep)
		{
			usleep(100);
			if (get_ms()
				- start_sleeping > s->philo->time_to_death)
				break ;
		}
	}
	pthread_mutex_lock(s->print);
	if (*s->are_alive)
		printf("%ld %d is thinking\n", get_ms() - *s->start, s->philo->id + 1);
	pthread_mutex_unlock(s->print);
	usleep(500);
	set_philo_deathtime(s, start_sleeping);
}
