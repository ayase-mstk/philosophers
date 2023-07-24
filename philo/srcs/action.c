/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hagewahi <hagewahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:23:50 by mahayase          #+#    #+#             */
/*   Updated: 2023/07/24 14:21:30 by hagewahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_string(t_env *env, unsigned long time, int num, char *str)
{
	pthread_mutex_lock(&env->info->print_mutex);
	if (env->info->print_flag)
		printf("%ld %d %s\n", (time - env->info->start_time), num, str);
	pthread_mutex_unlock(&env->info->print_mutex);
}

unsigned long	get_time(void)
{
	struct timeval	tv;
	unsigned long	msec;

	gettimeofday(&tv, NULL);
	msec = tv.tv_sec * (unsigned long)1000 + tv.tv_usec / 1000;
	return (msec);
}

int	eating_philo(t_env *env)
{
	if (check_break(env))
		return (1);
	pthread_mutex_lock(&env->info->forks[env->philo->r_forks]);
	if (env->philo->l_forks == env->philo->r_forks)
	{
		print_string(env, get_time(), env->philo->num, "has taken a fork");
		pthread_mutex_unlock(&env->info->forks[env->philo->r_forks]);
		return (1);
	}
	pthread_mutex_lock(&env->info->forks[env->philo->l_forks]);
	print_string(env, get_time(), env->philo->num, "has taken a fork");
	print_string(env, get_time(), env->philo->num, "is eating");
	reset_deathtime(env);
	wait_philo(env->info->eat);
	pthread_mutex_unlock(&env->info->forks[env->philo->r_forks]);
	pthread_mutex_unlock(&env->info->forks[env->philo->l_forks]);
	pthread_mutex_lock(&env->info->meal_mutex);
	env->philo->eat_count++;
	pthread_mutex_unlock(&env->info->meal_mutex);
	return (0);
}

int	sleeping_philo(t_env *env)
{
	if (check_break(env))
		return (1);
	print_string(env, get_time(), env->philo->num, "is sleeping");
	wait_philo(env->info->sleep);
	return (0);
}

int	thinking_philo(t_env *env)
{
	if (check_break(env))
		return (1);
	print_string(env, get_time(), env->philo->num, "is thinking");
	return (0);
}
