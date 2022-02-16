/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:49:51 by amyroshn          #+#    #+#             */
/*   Updated: 2022/02/16 12:23:18 by amyroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philo.h"

long	get_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000);
}

t_bool	philo_fork_init(t_philo **phils, t_fork **forks, t_settings *set)
{
	int	i;

	i = 0;
	if (!phils || !forks)
		return (FALSE);
	while (i < set->number_of_philo)
	{
		phils[i] = philo_init(i, set->time_to_die, set->times_eat);
		forks[i] = fork_init(i);
		if (!forks[i] || !phils[i])
		{
			while (i >= 0)
			{
				free(phils[i]);
				free(forks[i]);
				i--;
			}
			free(phils);
			free(forks);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

int	main(int ac, char **av)
{
	t_settings	*set;
	t_philo		**philos;
	t_fork		**forks;

	if (ac != 5 && ac != 6)
	{
		printf("Wrong args count\n");
		return (1);
	}
	set = parse_args(ac, av);
	if (!set)
		return (1);
	philos = (t_philo **) malloc(sizeof(t_philo) * set->number_of_philo);
	forks = (t_fork **) malloc(sizeof(t_fork) * set->number_of_philo);
	if (!philo_fork_init(philos, forks, set))
	{
		free(set);
		return (1);
	}
	set_and_start_threads(philos, forks, set);
	free_forks(forks, set->number_of_philo);
	free_philos(philos, set->number_of_philo);
	free(set);
	return (0);
}
