#include "philo_bonus.h"

sem_t	*init_forks(t_env *env)
{
	sem_t	*forks;
	// int		i;

	forks = sem_open("/forks", O_CREAT, 0666, env->nb_philo);
	if (forks == SEM_FAILED)
		return (NULL);
	// i = 0;
	// while (i < env->nb_philo)
	// {
	// 	sem_wait(forks);
	// 	i++;
	// }
	return (forks);
}

t_env	*init_env(int ac, char *av)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->nb_philo = ft_atoi(av[1]);
	env->time_to_die = ft_atoi(av[2]);
	env->time_to_eat = ft_atoi(av[3]);
	env->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		env->nb_eat = ft_atoi(av[5]);
	else
		env->nb_eat = -1;
	env->start_time = 0;
	env->forks = init_forks(env);
	return (env);
}

// t_philo	*init_philo(t_env *env)
// {

// }

void	start_meal(t_env *env, t_philo *philo)
{
}



int	main(int ac, char *av)
{
	t_env	*env;
	t_philo	*philo;

	if (ac < 5 || ac > 6)
	{
		printf("Error: wrong number of arguments\n");
		exit (1);
	}
	env = init_env(ac, av);
	if (!env)
		exit(1);
	philo = init_philo(env);
	start_meal(env, philo);
	return (0);
}
