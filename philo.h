/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahayase <mahayase@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 17:21:12 by mahayase          #+#    #+#             */
/*   Updated: 2023/05/26 18:32:06 by mahayase         ###   ########.fr       */
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
# include <pthread.h>

typedef struct s_philo
{
	int 			num;
	pthread_t		thread_id;
	pthread_mutex_t	*r_forks;
	pthread_mutex_t	*l_forks;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_times_each_philo_must_eat;
}	t_philo;

typedef struct s_env
{
	t_philo			**philo;
	pthread_mutex_t	*forks;
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_times_each_philo_must_eat;
}	t_env;

t_env			*init_env(char **av);
pthread_mutex_t	*init_forks(int num_of_philo);
t_philo			*create_philo(t_env *env, int num);
void			create_watchman(t_env *env);
void			*philo_routine(t_philo *philo);
void			*watchman_routine(t_env *env);

#endif