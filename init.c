/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hagewahi <hagewahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:55:50 by hagewahi          #+#    #+#             */
/*   Updated: 2023/05/27 22:42:58 by hagewahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_time(t_info *info, t_time *time)
{
	time->die = info->die;
	time->eat = info->eat;
	time->sleep = info->sleep;
	time->num_of_eat = info->num_of_eat;
}

t_info	*init_info(char **av)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	info->num_of_philo = atoi(av[1]);
	info->die = ft_atoi(av[2]);
	info->eat = ft_atoi(av[3]);
	info->sleep = ft_atoi(av[4]);
	info->num_of_eat = ft_atoi(av[5]);
	pthread_mutex_init(&info->dead_mutex, NULL);
	pthread_mutex_init(&info->meal_mutex, NULL);
	info->someone_died = true;
	info->everyone_ate_meal = true;
	info->philo = NULL;
	info->forks = NULL;
	return (info);
}

pthread_mutex_t	*init_forks(int num_of_philo)
{
	int	i;
	pthread_mutex_t	*forks;

	i = 0;
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num_of_philo);
	while (i < num_of_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

void	init_philo(t_philo *philo, t_info *info, int num)
{
	pthread_mutex_init(&philo->philo_mutex, NULL);
	philo->num = num + 1;
	philo->borntime = 0;
	philo->alive = 1;
	philo->r_forks = &info->forks[philo->num];
	philo->l_forks = &info->forks[(philo->num + 1) % info->num_of_philo];
	init_time(info, &philo->time);
}

void	create_watchman(t_philo *philo)
{
	pthread_t thread_id;
	int				ret;

	ret = pthread_create(&thread_id, NULL, (void *)watchman_routine, philo);
	if (ret != 0)
		strerror(errno);
	ret = pthread_join(thread_id, NULL);
	if (ret != 0)
		exit(1);
}
