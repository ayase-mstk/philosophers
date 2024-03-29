/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super_watchman.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hagewahi <hagewahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:24:03 by mahayase          #+#    #+#             */
/*   Updated: 2023/07/24 16:12:23 by hagewahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	kill_thread(t_env *env, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philo)
	{
		pthread_join(env[i].philo->thread_id, NULL);
		i++;
	}
}

int	check_dead_or_alive(t_env *env, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philo)
	{
		pthread_mutex_lock(&info->dead_mutex);
		if ((int)(get_time() - env[i].philo->last_meal_time) \
				> info->die)
		{
			info->someone_died = true;
			pthread_mutex_unlock(&info->dead_mutex);
			print_string(env, get_time(), i + 1, "died");
			pthread_mutex_lock(&info->print_mutex);
			info->print_flag = false;
			pthread_mutex_unlock(&info->print_mutex);
			return (1);
		}
		pthread_mutex_unlock(&info->dead_mutex);
		i++;
	}
	return (0);
}

int	check_had_eaten(t_env *env, t_info *info)
{
	int	i;
	int	flag;

	i = 0;
	flag = 1;
	while (i < info->num_of_philo)
	{
		pthread_mutex_lock(&info->meal_mutex);
		if (env[i].philo->eat_count > info->num_of_eat)
		{
			flag = 0;
			pthread_mutex_unlock(&info->meal_mutex);
			break ;
		}
		pthread_mutex_unlock(&info->meal_mutex);
		i++;
	}
	return (flag);
}

void	superwatchman(t_env *env, t_info *info)
{
	while (1)
	{
		if (check_dead_or_alive(env, info))
		{
			kill_thread(env, info);
			printf("dead end\n");
			break ;
		}
		if (info->num_of_eat && !check_had_eaten(env, info))
		{
			pthread_mutex_lock(&info->meal_mutex);
			info->everyone_ate_meal = true;
			pthread_mutex_unlock(&info->meal_mutex);
			kill_thread(env, info);
			printf("happy end\n");
			break ;
		}
		usleep(100);
	}
}
