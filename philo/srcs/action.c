#include "philo.h"

void	reset_deathtime(t_env *env)
{
	pthread_mutex_lock(&env->info->dead_mutex);
	env->philo->last_meal_time = get_time();
	pthread_mutex_unlock(&env->info->dead_mutex);
}

void	take_forks_philo(t_env *env)
{
	pthread_mutex_lock(&env->info->forks[env->philo->r_forks]);
	pthread_mutex_lock(&env->info->forks[env->philo->l_forks]);
	print_string(env, get_time(), env->philo->num, "has taken a fork");
}

void	eating_philo(t_env *env)
{
	print_string(env, get_time(), env->philo->num, "is eating");
	reset_deathtime(env);
	pthread_mutex_lock(&env->info->meal_mutex);
	env->philo->eat_count++;
	pthread_mutex_unlock(&env->info->meal_mutex);
	usleep(env->info->eat * 1000);
	pthread_mutex_unlock(&env->info->forks[env->philo->r_forks]);
	pthread_mutex_unlock(&env->info->forks[env->philo->l_forks]);
}

void	sleeping_philo(t_env *env)
{
	print_string(env, get_time(), env->philo->num, "is sleeping");
	usleep(env->info->sleep * 1000);
}

void	thinking_philo(t_env *env)
{
	print_string(env, get_time(), env->philo->num, "is thinking");
}