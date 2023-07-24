/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hagewahi <hagewahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:56:05 by hagewahi          #+#    #+#             */
/*   Updated: 2023/07/24 16:14:48 by hagewahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_philo(int time)
{
	unsigned long	start;

	start = get_time();
	while (1)
	{
		if ((int)(get_time() - start) \
					>= time)
			break ;
		usleep(10);
	}
}

int	check_break(t_env *env)
{
	pthread_mutex_lock(&env->info->dead_mutex);
	if (env->info->someone_died)
	{
		pthread_mutex_unlock(&env->info->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&env->info->dead_mutex);
	pthread_mutex_lock(&env->info->meal_mutex);
	if (env->info->everyone_ate_meal)
	{
		pthread_mutex_unlock(&env->info->meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&env->info->meal_mutex);
	return (0);
}

void	*philo_routine(t_env *env)
{
	reset_deathtime(env);
	while (1)
	{
		if (eating_philo(env))
			break ;
		if (sleeping_philo(env))
			break ;
		if (thinking_philo(env))
			break ;
	}
	return (NULL);
}
