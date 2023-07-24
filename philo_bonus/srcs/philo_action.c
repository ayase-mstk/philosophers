/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hagewahi <hagewahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:57:59 by hagewahi          #+#    #+#             */
/*   Updated: 2023/07/24 18:30:59 by hagewahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	wait_philo(int time)
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

static int	check_death(t_env *env)
{
	if ((int)(get_time() - env->last_meal) \
		> env->time_to_die)
	{
		print_string(env, get_time(), env->id, "died");
		return (1);
	}
	return (0);
}

void	eating_philo(t_env *env)
{
	if (check_death(env))
		exit(DEATH);
	usleep(env->id * 100);
	sem_wait(env->forks);
	sem_wait(env->forks);
	print_string(env, get_time(), env->id, "has taken a fork");
	if (check_death(env))
	{
		sem_post(env->forks);
		exit(DEATH);
	}
	print_string(env, get_time(), env->id, "is eating");
	env->last_meal = get_time();
	wait_philo(env->time_to_eat);
	sem_post(env->forks);
	sem_post(env->forks);
	if (env->max_eat > 0)
		env->max_eat--;
	else if (env->max_eat == 0)
		exit(MAX_EAT);
}

void	sleeping_philo(t_env *env)
{
	if (check_death(env))
		exit(DEATH);
	print_string(env, get_time(), env->id, "is sleeping");
	wait_philo(env->time_to_sleep);
}

void	thinking_philo(t_env *env)
{
	if (check_death(env))
		exit(DEATH);
	print_string(env, get_time(), env->id, "is thinking");
}
