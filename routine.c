#include "philo.h"

void	*philo_routine(t_philo *philo)
{
	struct timeval tv;

	// usleep(1000);
	gettimeofday(&tv, NULL);
	printf("born as philo%d\n", philo->num);
	while (philo->time_to_die && philo->num_of_times_each_philo_must_eat)
	{
		if (philo->num % 2 == 0)
			usleep(50);
		if (pthread_mutex_trylock(philo->r_forks) == 0 && pthread_mutex_trylock(philo->l_forks) == 0)
		{
			printf("%d %d has taken a fork\n", tv.tv_usec ,philo->num);
			// usleep(philo->time_to_eat);
			// tmp_time_to_die += philo->time_to_die;
			philo->num_of_times_each_philo_must_eat--;
			pthread_mutex_unlock(philo->r_forks);
			pthread_mutex_unlock(philo->l_forks);
		}
		philo->time_to_die--;
	}
	return (NULL);
}

int	check_dead_or_alive(t_env *env)
{
	int i;

	i = 0;
	while (i < env->num_of_philo)
	{
		if (env->philo[i]->time_to_die)
			return (1);
		i++;
	}
	return (0);
}

int	check_had_eaten(t_env *env)
{
	int i;

	i = 0;
	while (i < env->num_of_philo)
	{
		if (env->philo[i]->num_of_times_each_philo_must_eat)
			return (1);
		i++;
	}
	return (0);
}

void	*watchman_routine(t_env *env)
{
	int i;

	i = 0;
	while (check_dead_or_alive(env) && check_had_eaten(env))
	{
		i = 0;
		while (i < env->num_of_philo)
		{
			if (env->philo[i]->time_to_die == 0)
				printf("philo%d is dead\n", env->philo[i]->num);
			i++;
		}
	}
	return (NULL);
}
