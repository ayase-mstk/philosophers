/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hagewahi <hagewahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:58:17 by hagewahi          #+#    #+#             */
/*   Updated: 2023/07/24 18:02:39 by hagewahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_other_philo(t_env *env, pid_t *philo_pid, pid_t pid)
{
	size_t	i;

	i = 0;
	while (i < (size_t)env->nb_philo)
	{
		if (pid == philo_pid[i])
		{
			i++;
			continue ;
		}
		kill(philo_pid[i], SIGTERM);
		i++;
	}
}

void	wait_all_philo(t_env *env, pid_t *philo_pid)
{
	size_t	i;
	pid_t	pid;
	pid_t	ret;
	int		status;

	i = 0;
	pid = waitpid(-1, &status, 0);
	if (pid < 0)
		exit_error("waitpid");
	if (WIFEXITED(status) && WEXITSTATUS(status) == DEATH)
		kill_other_philo(env, philo_pid, pid);
	i = 0;
	while (i < (size_t)env->nb_philo)
	{
		if (philo_pid[i] != pid)
		{
			ret = waitpid(philo_pid[i], &status, 0);
			if (ret < 0)
				exit_error("waitpid");
		}
		i++;
	}
}

void	delete_semafork(t_env *env)
{
	sem_close(env->forks);
	sem_unlink(env->fork_name);
	sem_close(env->write);
	sem_unlink(env->write_name);
}

void	free_all(t_env *env)
{
	delete_semafork(env);
	free(env);
}
