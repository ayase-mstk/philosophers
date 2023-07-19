/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahayase <mahayase@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 17:21:12 by mahayase          #+#    #+#             */
/*   Updated: 2023/07/19 19:12:08 by mahayase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include <pthread.h>

typedef struct s_philo
{
	pthread_t		thread_id;
	unsigned int	r_forks;
	unsigned int	l_forks;
	int				num;
	unsigned long	last_meal_time;
	int				eat_count;
	bool			alive;
}	t_philo;

typedef struct s_info
{
	unsigned long	start_time;
	pthread_mutex_t	*forks;
	int				num_of_philo;
	int				die;
	int				eat;
	int				sleep;
	int				num_of_eat;
	bool			someone_died;
	bool			everyone_ate_meal;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	print_mutex;
}	t_info;

typedef struct s_env
{
	t_philo	*philo;
	t_info	*info;
}	t_env;

int				ft_atoi(const char *str);
int				ft_strlen(char *str);
unsigned long	get_time(void);
void			print_string(t_env *env, unsigned long time, \
							int num, char *str);
void			destroy_forks(t_info *info);
t_info			*init_info(int ac, char **av);
pthread_mutex_t	*init_forks(int num_of_philo);
void			init_philo(t_philo *philo, t_info *info, int num);
void			init_philos(t_philo *philos, t_info *info);
void			superwatchman(t_env *env, t_info *info);
void			start_threads(t_env *env, t_philo *philo, t_info *info);
void			*philo_routine(t_env *env);
void			wait_eat(t_env *env);
void			wait_sleep(t_env *env);
int				check_break(t_env *env);
void			reset_deathtime(t_env *env);
int				take_forks_philo(t_env *env);
int				eating_philo(t_env *env);
int				sleeping_philo(t_env *env);
int				thinking_philo(t_env *env);

#endif