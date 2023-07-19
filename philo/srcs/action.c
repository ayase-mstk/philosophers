/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahayase <mahayase@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:23:50 by mahayase          #+#    #+#             */
/*   Updated: 2023/07/19 19:11:39 by mahayase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	reset_deathtime(t_env *env)
{
	pthread_mutex_lock(&env->info->dead_mutex);
	env->philo->last_meal_time = get_time();
	pthread_mutex_unlock(&env->info->dead_mutex);
}

int	take_forks_philo(t_env *env)
{
	if (check_break(env))
		return (1);
	pthread_mutex_lock(&env->info->forks[env->philo->r_forks]);
	if (env->philo->l_forks == env->philo->r_forks)
	{
		print_string(env, get_time(), env->philo->num, "has taken a fork");
		pthread_mutex_unlock(&env->info->forks[env->philo->l_forks]);
		return (1);
	}
	pthread_mutex_lock(&env->info->forks[env->philo->l_forks]);
	print_string(env, get_time(), env->philo->num, "has taken a fork");
	return (0);
}

int	eating_philo(t_env *env)
{
	if (check_break(env))
		return (1);
	print_string(env, get_time(), env->philo->num, "is eating");
	reset_deathtime(env);
	pthread_mutex_lock(&env->info->meal_mutex);
	env->philo->eat_count++;
	pthread_mutex_unlock(&env->info->meal_mutex);
	wait_eat(env);
	pthread_mutex_unlock(&env->info->forks[env->philo->r_forks]);
	pthread_mutex_unlock(&env->info->forks[env->philo->l_forks]);
	return (0);
}

int	sleeping_philo(t_env *env)
{
	if (check_break(env))
		return (1);
	print_string(env, get_time(), env->philo->num, "is sleeping");
	wait_sleep(env);
	return (0);
}

int	thinking_philo(t_env *env)
{
	if (check_break(env))
		return (1);
	print_string(env, get_time(), env->philo->num, "is thinking");
	return (0);
}
