/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:04:50 by amyroshn          #+#    #+#             */
/*   Updated: 2022/02/16 12:19:24 by amyroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philo.h"

t_philo	*philo_init(int id, int time_to_death, int times_eat)
{
	t_philo	*p;

	p = (t_philo *) malloc(sizeof(t_philo));
	if (!p)
		return (NULL);
	p->id = id;
	p->left = NULL;
	p->rigth = NULL;
	p->time_to_death = time_to_death;
	p->times_eat = times_eat;
	return (p);
}

t_fork	*fork_init(int id)
{
	t_fork	*fork;

	fork = (t_fork *) malloc(sizeof(t_fork));
	if (!fork)
		return (NULL);
	fork->id = id;
	fork->isfree = TRUE;
	return (fork);
}

t_settings	*set_settings(int philo, int die, int eat, int sleep)
{
	t_settings	*s;

	s = (t_settings *) malloc(sizeof(t_settings));
	if (!s)
		return (NULL);
	s->number_of_philo = philo;
	s->time_to_die = die;
	s->time_to_eat = eat;
	s->time_to_sleep = sleep;
	s->times_eat = -1;
	s->are_alive = NULL;
	s->start = NULL;
	s->philo = NULL;
	s->forks = NULL;
	return (s);
}

void	free_philos(t_philo **philo, int count)
{
	int	i;

	if (!philo)
		return ;
	i = 0;
	while (i < count)
	{
		free(philo[i]);
		i++;
	}
	free(philo);
}

void	free_forks(t_fork **forks, int count)
{
	int	i;

	i = 0;
	if (!forks)
		return ;
	while (i < count)
	{
		free(forks[i]);
		i++;
	}
	free(forks);
}
