#include "philo_bonus.h"

static void	wait_philo(int time)
{
	unsigned long	start;

	start = get_time();
	while (1)
	{
		if ((int)(get_time() - start) \
					>= time)
			break ;
		usleep(10);
	}
}

int	eating_philo(t_env *env)
{
	if (check_death(env))
		return (1);
	usleep(env->id * 100);
	sem_wait(env->forks);
	print_string(env, get_time(), env->id, "has taken a fork");
	if (check_death(env))
		return (1);
	print_string(env, get_time(), env->id, "is eating");
	env->last_meal = get_time();
	wait_philo(env->time_to_eat);
	sem_post(env->forks);
	if (env->max_eat > 0)
		env->max_eat--;
	else if (env->max_eat == 0)
		exit(MAX_EAT);
	return (0);
}

int	sleeping_philo(t_env *env)
{
	if (check_death(env))
		return (1);
	print_string(env, get_time(), env->id, "is sleeping");
	wait_philo(env->time_to_sleep);
	return (0);
}

int	thinking_philo(t_env *env)
{
	if (check_death(env))
		return (1);
	print_string(env, get_time(), env->id, "is thinking");
	return (0);
}
