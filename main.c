/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahayase <mahayase@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 17:21:09 by mahayase          #+#    #+#             */
/*   Updated: 2023/05/26 18:31:22 by mahayase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_threads(t_env *env)
{
	int	i;

	i = 0;
	env->philo = (t_philo **)malloc(sizeof(t_philo *) * env->num_of_philo);
	while (i < env->num_of_philo)
	{
		env->philo[i] = create_philo(env, i);
		i++;
	}
	create_watchman(env);
}

int	main(int ac, char **av)
{
	t_env	*env;
	if (ac != 6)
		return (0);
	env = init_env(av);
	env->forks = init_forks(env->num_of_philo);
	start_threads(env);
	return (0);
}
