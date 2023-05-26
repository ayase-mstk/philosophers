/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahayase <mahayase@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 17:21:09 by mahayase          #+#    #+#             */
/*   Updated: 2023/05/25 18:33:32 by mahayase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*start_routine(t_philo *philo)
{
	printf("philo number : %d\n", philo->num);
	return (NULL);
}

void	start_threads(char **av)
{
	int	i;
	int	ret;
	int number_of_philo;
	pthread_t *thread_id;
	struct s_philo	*philo;

	i = 0;
	number_of_philo = atoi(av[1]);
	thread_id = malloc(sizeof(int) * number_of_philo);
	philo = malloc(sizeof(t_philo) * (number_of_philo));
	while (i < number_of_philo)
	{
		philo[i]->num = i;
		philo[i]->time_to_die = atoi(av[2]);
		philo[i]->time_to_eat = atoi(av[3]);
		philo[i]->time_to_sleep = atoi(av[4]);
		ret = pthread_create(&thread_id[i], NULL, (void *)start_routine, philo[i]);
		if (ret != 0)
			exit(1);
		ret = pthread_join(thread_id[i], NULL);
		if (ret != 0)
			exit(1);
		i++;
	}
}

int	main(int ac, char **av)
{
	if (ac != 5)
		return (0);
	start_threads(av);
	// pthred_mutex_lock(&forks);
	// pthred_mutex_unlock(&forks);
	return (0);
}
