#include "philo.h"

void	kill_thread(t_env *env, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philo)
	{
		pthread_join(env[i].philo->thread_id, NULL);
		i++;
	}
}

int	check_dead_or_alive(t_env *env, t_info *info)
{
	int 						i;
	int							res;

	i = 0;
	res = 1;
	while (i < info->num_of_philo && res)
	{
		pthread_mutex_lock(&info->dead_mutex);
		if ((int)(get_time() - env[i].philo->last_meal_time) \
						> info->die)
			res = 0;
		pthread_mutex_unlock(&info->dead_mutex);
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
		pthread_mutex_lock(&info->meal_mutex);
		if (env[i].philo->eat_count < info->num_of_eat)
			ret = 1;
		pthread_mutex_unlock(&info->meal_mutex);
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
			print_string(env, get_time(), 0, "someone died");
			break ;
		}
		if (!check_had_eaten(env, info))
		{
			pthread_mutex_lock(&info->meal_mutex);
			info->everyone_ate_meal = false;
			pthread_mutex_unlock(&info->meal_mutex);
			kill_thread(env, info);
			print_string(env, get_time(), 0, "everyone ate meal");
			break ;
		}	
		usleep(50000);
	}
}
