/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hagewahi <hagewahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:58:11 by hagewahi          #+#    #+#             */
/*   Updated: 2023/07/24 18:01:22 by hagewahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_death(t_env *env)
{
	if ((int)(get_time() - env->last_meal) \
		> env->time_to_die)
	{
		print_string(env, get_time(), env->id, "died");
		sem_wait(env->write);
		env->print_flag = false;
		sem_post(env->write);
		return (1);
	}
	return (0);
}

void	*philo_life(t_env *env)
{
	env->last_meal = get_time();
	while (1)
	{
		if (eating_philo(env))
			break ;
		if (sleeping_philo(env))
			break ;
		if (thinking_philo(env))
			break ;
	}
	exit (DEATH);
}
