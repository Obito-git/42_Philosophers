/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:40:39 by amyroshn          #+#    #+#             */
/*   Updated: 2022/02/16 12:41:28 by amyroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# define TRUE 1
# define FALSE 0

typedef int	t_bool;

typedef struct s_settings
{
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*print;
	int				number_of_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			times_eat;
	long			*start;
	long			*are_alive;
	struct s_fork	**forks;
	struct s_philo	*philo;
}	t_settings;

typedef struct s_fork
{
	int		id;
	t_bool	isfree;
}	t_fork;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	struct s_fork	*left;
	struct s_fork	*rigth;
	long			time_to_death;
	long			times_eat;
}	t_philo;

t_settings	*set_settings(int philo, int die, int eat, int sleep);
t_fork		*fork_init(int id);
t_philo		*philo_init(int id, int time_to_death, int times_eat);
t_settings	*parse_args(int ac, char **av);
void		free_forks(t_fork **forks, int count);
void		free_philos(t_philo **philo, int count);
void		set_and_start_threads(t_philo **p, t_fork **f, t_settings *s);
void		*routine(void *arg);
void		go_eat(t_settings *s);
void		go_sleep(t_settings *s);
long		get_ms(void);
void		set_philo_deathtime(t_settings *s, long start);
//libft
size_t		ft_strlen(const char *str);
long		ft_atol_sample(char *numb);
t_bool		ft_isdigit(int c);
long		ft_pow(long nb, int power);
int			ft_strcmp(char *s1, char *s2);
#endif
