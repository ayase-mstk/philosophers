#include "philo_bonus.h"

void	kill_other_philo(t_env *env, pid_t *philo_pid, int status)
{
	size_t	i;

	i = 0;
	while (i < (size_t)env->nb_philo)
	{
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == DEATH)
			{
				i++;
				continue ;
			}
		}
		kill(philo_pid[i], SIGKILL);
		i++;
	}
}

void	wait_all_philo(t_env *env, pid_t *philo_pid)
{
	size_t	i;
	pid_t	pid;
	int		status;
	int		everyone_ate;

	i = 0;
	everyone_ate = 0;
	pid = waitpid(-1, &status, 0);
	if (status < 0)
		exit_error("waitpid");
	if (WIFEXITED(status) && WEXITSTATUS(status) == DEATH)
		kill_other_philo(env, philo_pid, status);
	i = 0;
	while (i < (size_t)env->nb_philo)
	{
		if (philo_pid[i] != pid)
		{
			waitpid(philo_pid[i], &status, 0);
			if (status < 0)
				exit_error("waitpid");
			else if (WIFEXITED(status) && WEXITSTATUS(status) == MAX_EAT)
				everyone_ate++;
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
