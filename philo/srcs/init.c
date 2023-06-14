/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahayase <mahayase@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:55:50 by hagewahi          #+#    #+#             */
/*   Updated: 2023/06/14 21:53:00 by mahayase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_info	*init_info(int ac, char **av)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	info->num_of_philo = ft_atoi(av[1]);
	info->die = ft_atoi(av[2]);
	info->eat = ft_atoi(av[3]);
	info->sleep = ft_atoi(av[4]);
	if (ac == 6)
		info->num_of_eat = ft_atoi(av[5]);
	else
		info->num_of_eat = 0;
	pthread_mutex_init(&info->dead_mutex, NULL);
	pthread_mutex_init(&info->meal_mutex, NULL);
	pthread_mutex_init(&info->print_mutex, NULL);
	info->someone_died = true;
	info->everyone_ate_meal = true;
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
	philo->num = num + 1;
	philo->last_meal_time = 0;
	philo->eat_count = 0;
	philo->r_forks = philo->num - 1;
	philo->l_forks = (philo->num) % (info->num_of_philo);
	philo->alive = true;
}
