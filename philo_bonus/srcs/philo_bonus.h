/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hagewahi <hagewahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:58:07 by hagewahi          #+#    #+#             */
/*   Updated: 2023/07/24 18:25:02 by hagewahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>

# define DEATH 1
# define MAX_EAT 2

typedef struct s_env
{
	char			*fork_name;
	sem_t			*forks;
	char			*write_name;
	sem_t			*write;
	int				id;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat;
	unsigned long	last_meal;
	unsigned long	start_time;
}	t_env;

unsigned long	get_time(void);
void			print_string(t_env *env, unsigned long time, \
							int num, char *str);
void			exit_error(char *str);
int				ft_atoi(const char *str);
t_env			*init_env(int ac, char **av);
void			create_philo(t_env *env);
void			wait_all_philo(t_env *env, pid_t *philo_pid);
void			delete_semafork(t_env *env);
void			free_all(t_env *env);
void			*philo_life(t_env *env);
void			eating_philo(t_env *env);
void			sleeping_philo(t_env *env);
void			thinking_philo(t_env *env);
int				main(int ac, char **av);

#endif