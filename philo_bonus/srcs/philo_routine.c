/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hagewahi <hagewahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:58:11 by hagewahi          #+#    #+#             */
/*   Updated: 2023/07/24 18:25:49 by hagewahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*philo_life(t_env *env)
{
	env->last_meal = get_time();
	while (1)
	{
		eating_philo(env);
		sleeping_philo(env);
		thinking_philo(env);
	}
	exit (DEATH);
}
