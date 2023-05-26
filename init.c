#include "philo.h"

t_env	*init_env(char **av)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	env->num_of_philo = atoi(av[1]);
	env->time_to_die = atoi(av[2]);
	env->time_to_eat = atoi(av[3]);
	env->time_to_sleep = atoi(av[4]);
	env->num_of_times_each_philo_must_eat = atoi(av[5]);
	env->philo = NULL;
	env->forks = NULL;
	return (env);
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

t_philo	*create_philo(t_env *env, int num)
{
	t_philo	*philo;
	int ret;

	philo = malloc(sizeof(t_philo));
	philo->num = num + 1;
	philo->r_forks = &env->forks[philo->num % env->num_of_philo];
	philo->l_forks = &env->forks[(philo->num + 1) % env->num_of_philo];
	philo->time_to_die = env->time_to_die;
	philo->time_to_eat = env->time_to_eat;
	philo->time_to_sleep = env->time_to_sleep;
	philo->num_of_times_each_philo_must_eat = env->num_of_times_each_philo_must_eat;
	ret = pthread_create(&philo->thread_id, NULL, (void *)philo_routine, philo);
	if (ret != 0)
		strerror(errno);
	ret = pthread_detach(philo->thread_id);
	if (ret != 0)
		exit(1);
	return (philo);
}

void	create_watchman(t_env *env)
{
	pthread_t	thread_id;
	int			ret;

	ret = pthread_create(&thread_id, NULL, (void *)watchman_routine, env);
	if (ret != 0)
		strerror(errno);
	ret = pthread_join(thread_id, NULL);
	if (ret != 0)
		exit(1);
}
