/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahayase <mahayase@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:56:05 by hagewahi          #+#    #+#             */
/*   Updated: 2023/06/14 21:46:06 by mahayase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_time(void)
{
	struct timeval  tv;
	unsigned long   msec;

	gettimeofday( &tv, NULL );
	msec = tv.tv_sec * (unsigned long)1000 + tv.tv_usec / 1000;
	return (msec);
}

void	print_string(t_env *env, unsigned long time, int num, char *str)
{
	pthread_mutex_lock(&env->info->print_mutex);
	printf("%*ld %d %s\n", 6, (time - env->info->start_time), num, str);
	pthread_mutex_unlock(&env->info->print_mutex);
}

int	check_break(t_env *env)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&env->info->dead_mutex);
	if (!env->info->someone_died)
		res = 1;
	pthread_mutex_unlock(&env->info->dead_mutex);
	pthread_mutex_lock(&env->info->meal_mutex);
	if (!env->info->everyone_ate_meal)
		res = 1;
	pthread_mutex_unlock(&env->info->meal_mutex);
	return (res);
}

void	*philo_routine(t_env *env)
{
	unsigned int	tmp_fork;

	reset_deathtime(env);
	if (env->philo->num % 2 == 0)
	{
		tmp_fork = env->philo->l_forks;
		env->philo->l_forks = env->philo->r_forks;
		env->philo->r_forks = tmp_fork;
		usleep(1000);
	}
	while (1)
	{
		if (check_break(env))
			break ;
		take_forks_philo(env);
		eating_philo(env);
		sleeping_philo(env);
		thinking_philo(env);
	}
	return (NULL);
}
