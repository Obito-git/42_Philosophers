#include "../philo.h"
t_settings **set_thread_args(t_philo **p, t_fork **f, t_settings *s, long *t)
{
	t_settings	**res;
	int			i;

	i = 0;
	res = (t_settings **) malloc (sizeof(t_settings) * s->number_of_philo);
	if (!res)
		return (NULL);
	while (i < s->number_of_philo)
	{
		res[i] = set_settings(s->number_of_philo, s->time_to_die,
								s->time_to_eat, s->time_to_sleep);
		if (!res[i])
		{
			while (i >= 0)
				free(res[i--]);
			free(res);
			return (NULL);
		}
		res[i]->philo = p[i];
		res[i]->forks = f;
		res[i]->ms_from_start = t;
		res[i]->are_alive = t;
		i++;
	}
	return (res);
}

void	start_and_wait(t_philo **p, t_settings **args, t_settings *s)
{
	int	i;
	pthread_mutex_t	mutex;
	pthread_mutex_t	print;
	pthread_mutex_t	death;

	i = 0;

	if (!args)
		ft_printf("Malloc error!\n");
	pthread_mutex_init(&mutex, NULL); //protection
	pthread_mutex_init(&print, NULL); //protection
	pthread_mutex_init(&death, NULL); //protection
	while (args && i < s->number_of_philo)
	{
		args[i]->mutex = &mutex;
		args[i]->print = &print;
		args[i]->death= &death;
		if (pthread_create(&p[i]->thread, NULL, &routine, args[i]) != 0)
			perror("failed to created thread\n");
		i++;
	}
	i = 0;
	while (args && i < s->number_of_philo)
	{
		if (pthread_join(p[i]->thread, NULL) != 0)
			perror("Failed to join thread\n"); //FIXME
		i++;
	}
	pthread_mutex_destroy(&mutex);
	pthread_mutex_destroy(&print);
	pthread_mutex_destroy(&death);
	i = 0;
	while (args && i < s->number_of_philo)
		free(args[i++]);
	free(args);
}

void	set_and_start_threads(t_philo **p, t_fork **f, t_settings *s)
{
	t_settings	**args;
	long		*start_time;

	start_time = (long *) malloc(sizeof(long));
	if (!start_time)
		return ;
	args = set_thread_args(p, f, s, start_time);
	*start_time = get_current_time_ms();
	start_and_wait(p, args, s);
	free(start_time);
}
