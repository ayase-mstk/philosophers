#include "philo.h"

void	kill_thread(t_env *env, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philo)
	{
		pthread_detach(env[i].philo->thread_id);
		i++;
	}
}

int	check_dead_or_alive(t_env *env, t_info *info)
{
	int 						i;
	int							res;
	struct timeval	now;

	i = 0;
	res = 1;
	while (i < info->num_of_philo && res)
	{
		pthread_mutex_lock(&env[i].philo->philo_mutex);
		gettimeofday(&now, NULL);
		if (now.tv_usec - env[i].philo->borntime > env[i].philo->time.die)
			res = 0;
		pthread_mutex_unlock(&env[i].philo->philo_mutex);
		i++;
	}
	return (res);
}

int	check_had_eaten(t_env *env, t_info *info)
{
	int i;
	int	ret;

	i = 0;
	ret = 0;
	while (i < info->num_of_philo)
	{
		pthread_mutex_lock(&env[i].philo->philo_mutex);
		if (env[i].philo->time.num_of_eat)
			ret = 1;
		pthread_mutex_unlock(&env[i].philo->philo_mutex);
		i++;
	}
	return (ret);
}

void	superwatchman(t_env *env, t_info *info)
{
	while (1)
	{
		if (!check_dead_or_alive(env, info))
		{
			pthread_mutex_lock(&info->dead_mutex);
			info->someone_died = false;
			pthread_mutex_unlock(&info->dead_mutex);
			kill_thread(env, info);
			break ;
		}
		if (!check_had_eaten(env, info))
		{
			pthread_mutex_lock(&info->meal_mutex);
			info->everyone_ate_meal = false;
			pthread_mutex_unlock(&info->meal_mutex);
			kill_thread(env, info);
			break ;
		}	
		usleep(100);
	}
}
