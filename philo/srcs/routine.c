/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahayase <mahayase@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:56:05 by hagewahi          #+#    #+#             */
/*   Updated: 2023/06/15 17:52:28 by mahayase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_eat(t_env *env)
{
	while (1)
	{
		pthread_mutex_unlock(&env->info->dead_mutex);
		if (get_time() - env->philo->last_meal_time \
					>= (unsigned long)env->info->eat)
		{
			pthread_mutex_unlock(&env->info->dead_mutex);
			break ;
		}
		pthread_mutex_unlock(&env->info->dead_mutex);
		usleep(10);
	}
}

void	wait_sleep(t_env *env)
{
	while (1)
	{
		pthread_mutex_lock(&env->info->dead_mutex);
		if (get_time() - env->philo->last_meal_time \
					>= (unsigned long)env->info->sleep)
		{
			pthread_mutex_unlock(&env->info->dead_mutex);
			break ;
		}
		pthread_mutex_unlock(&env->info->dead_mutex);
		usleep(10);
	}
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
