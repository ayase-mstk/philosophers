/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahayase <mahayase@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 17:21:09 by mahayase          #+#    #+#             */
/*   Updated: 2023/06/14 21:04:06 by mahayase         ###   ########.fr       */
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
	printf("stop time ; %d\n", info->eat * 900);
	info->start_time = get_time();
	while (i < info->num_of_philo)
	{
		env[i].info = info;
		env[i].philo = &philo[i];
		ret = pthread_create(&philo[i].thread_id, NULL, (void *)philo_routine, &env[i]);
		if (ret != 0)
			exit(1);
		i++;
		// usleep(1000);
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

void	join_threads(t_env *env, t_info *info)
{
	int		i;

	i = 0;
	while (i < info->num_of_philo)
	{
		pthread_join(env[i].philo->thread_id, NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_env		*env;
	t_philo	*philo;
	t_info	*info;

	if (ac != 5 && ac != 6)
		return (0);
	info = init_info(ac, av); 
	info->forks = init_forks(info->num_of_philo);
	philo = (t_philo *)malloc(sizeof(t_philo) * info->num_of_philo);
	init_philos(philo, info);
	env = (t_env *)malloc(sizeof(t_env) * info->num_of_philo);
	start_threads(env, philo, info);
	superwatchman(env, info);
	// join_threads(env, info);
	free(philo);
	destroy_forks(info);
	free(info->forks);
	free(info);
	free(env);
	return (0);
}
