/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hagewahi <hagewahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 17:21:09 by mahayase          #+#    #+#             */
/*   Updated: 2023/05/27 23:31:08 by hagewahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_philo *philos, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philo)
	{
		init_philo(&philos[i], info, i);
		i++;
	}
}

void	start_threads(t_env *env, t_philo *philo, t_info *info)
{
	int	i;
	int	ret;

	i = 0;
	while (i < info->num_of_philo)
	{
		env[i].info = info;
		env[i].philo = &philo[i];
		ret = pthread_create(&philo[i].thread_id, NULL, (void *)philo_routine, &env[i]);
		if (ret != 0)
			exit(1);
		i++;
		usleep(100);
	}
	// i = 0;
	// while (i < info->num_of_philo)
	// {
	// 	ret = pthread_detach(env[i].philo->thread_id);
	// 	if (ret != 0)
	// 		exit(1);
	// 	i++;
	// }
}

int	main(int ac, char **av)
{
	t_env		*env;
	t_philo	*philo;
	t_info	*info;

	if (ac != 6)
		return (0);
	info = init_info(av);
	info->forks = init_forks(info->num_of_philo);
	philo = (t_philo *)malloc(sizeof(t_philo) * info->num_of_philo);
	init_philos(philo, info);
	env = (t_env *)malloc(sizeof(t_env) * info->num_of_philo);
	start_threads(env, philo, info);
	superwatchman(env, info);
	free_philo(env, info, philo);
	destroy_forks(info);
	free(info->forks);
	free(info);
	free(env);
	return (0);
}
