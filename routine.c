/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hagewahi <hagewahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:56:05 by hagewahi          #+#    #+#             */
/*   Updated: 2023/05/27 23:46:13 by hagewahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	printf("born as philo%d\n", env->philo->num);
	reset_borntime(env->philo);
	// create_watchman(env->philo);
	while (1)
	{
		if (env->philo->num % 2 == 0)
			usleep(50);
		if (check_break(env))
			break ;
		take_forks_philo(env->philo);
		eating_philo(env->philo);
		sleeping_philo(env->philo);
		thinking_philo(env->philo);
	}
	// free(philo);
	// philo = NULL;
	return (NULL);
}

void	*watchman_routine(t_env *env)
{
	struct timeval	now;
	t_philo					*philo;

	philo = env->philo;
	while (env->philo->alive != 0)
	{
		pthread_mutex_lock(&philo->philo_mutex);
		gettimeofday(&now, NULL);
		if (now.tv_usec - philo->borntime > philo->time.die)
		{
			printf("%ld %d died\n", now.tv_usec, philo->num);
			philo->alive = 0;
		}
		pthread_mutex_unlock(&philo->philo_mutex);
	}
	return (NULL);
}
