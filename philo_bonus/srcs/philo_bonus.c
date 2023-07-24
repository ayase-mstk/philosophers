/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hagewahi <hagewahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:57:33 by hagewahi          #+#    #+#             */
/*   Updated: 2023/07/24 17:58:37 by hagewahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_env	*init_env(int ac, char **av)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->id = 0;
	env->nb_philo = ft_atoi(av[1]);
	env->time_to_die = ft_atoi(av[2]);
	env->time_to_eat = ft_atoi(av[3]);
	env->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		env->max_eat = ft_atoi(av[5]);
	else
		env->max_eat = -1;
	env->start_time = 0;
	env->fork_name = "/forks";
	env->forks = sem_open(env->fork_name, O_CREAT, 0666, env->nb_philo / 2);
	if (env->forks == SEM_FAILED)
		exit_error("sem_open");
	env->write_name = "/write";
	env->write = sem_open(env->write_name, O_CREAT, 0666, 1);
	if (env->write == SEM_FAILED)
		exit_error("sem_open");
	env->print_flag = true;
	return (env);
}

void	create_philo(t_env *env)
{
	size_t	i;
	pid_t	*philo_pid;

	i = 0;
	philo_pid = (pid_t *)malloc(sizeof(pid_t) * env->nb_philo);
	if (!philo_pid)
		exit_error("malloc");
	env->start_time = get_time();
	while (i < (size_t)env->nb_philo)
	{
		env->id = i + 1;
		philo_pid[i] = fork();
		if (philo_pid[i] == 0)
			philo_life(env);
		else if (philo_pid[i] < 0)
			exit_error("fork");
		i++;
	}
	wait_all_philo(env, philo_pid);
	free(philo_pid);
}

int	main(int ac, char **av)
{
	t_env	*env;

	if (ac < 5 || ac > 6)
	{
		printf("Error: wrong number of arguments\n");
		exit (EXIT_FAILURE);
	}
	env = init_env(ac, av);
	if (!env)
		exit(EXIT_FAILURE);
	create_philo(env);
	free_all(env);
	return (0);
}
