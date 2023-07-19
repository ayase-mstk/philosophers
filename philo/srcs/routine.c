/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahayase <mahayase@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:56:05 by hagewahi          #+#    #+#             */
/*   Updated: 2023/07/19 19:14:48 by mahayase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_eat(t_env *env)
{
	unsigned long	start;

	start = get_time();
	while (1)
	{
		if ((int)(get_time() - start) \
					>= env->info->eat)
			break ;
		usleep(10);
	}
}

void	wait_sleep(t_env *env)
{
	unsigned long	start;

	start = get_time();
	while (1)
	{
		if ((int)(get_time() - start) \
					>= env->info->sleep)
			break ;
		usleep(10);
	}
}

int	check_break(t_env *env)
{
	pthread_mutex_lock(&env->info->dead_mutex);
	if (!env->info->someone_died)
	{
		pthread_mutex_unlock(&env->info->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&env->info->dead_mutex);
	pthread_mutex_lock(&env->info->meal_mutex);
	if (!env->info->everyone_ate_meal)
	{
		pthread_mutex_unlock(&env->info->meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&env->info->meal_mutex);
	return (0);
}

void	*philo_routine(t_env *env)
{
	unsigned int	tmp_fork;

	reset_deathtime(env);
	if (env->info->num_of_philo % 2 != 0)
	{
		if (env->philo->num % 2 == 0)
		{
			tmp_fork = env->philo->l_forks;
			env->philo->l_forks = env->philo->r_forks;
			env->philo->r_forks = tmp_fork;
			usleep(1000);
		}
	}
	while (1)
	{
		if (take_forks_philo(env))
			break ;
		if (eating_philo(env))
			break ;
		if (sleeping_philo(env))
			break ;
		if (thinking_philo(env))
			break ;
	}
	return (NULL);
}
