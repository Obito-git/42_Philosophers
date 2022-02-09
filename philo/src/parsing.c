#include "../philo.h"

static t_bool	check_numbformat(char **av, t_settings *set)
{
	if (set->time_to_die == 0
		&& (ft_strlen(av[2]) != 1 || av[2][0] != '0'))
		return (FALSE);
	if (set->time_to_eat == 0
		&& (ft_strlen(av[3]) != 1 || av[3][0] != '0'))
		return (FALSE);
	if (set->time_to_sleep == 0
		&& (ft_strlen(av[4]) != 1 || av[4][0] != '0'))
		return (FALSE);
	return (TRUE);
}

t_settings	*parse_args(char **av)
{
	t_settings	*set;

	set = set_settings(ft_atol_sample(av[1]), ft_atol_sample(av[2]),
						ft_atol_sample(av[3]), ft_atol_sample(av[4]));
	if (!check_numbformat(av, set) || (set->number_of_philo <= 0
		|| set->time_to_die < 0 || set->time_to_eat < 0
		|| set->time_to_sleep < 0))
	{
		if (!check_numbformat(av, set))
			ft_printf("Incorrect number format\n");
		else if (set->number_of_philo <= 0)
			ft_printf("Wrong philo count\n");
		else
			ft_printf("Time can't be negative\n");
		free(set);
		return (NULL);
	}
	return (set);
}
