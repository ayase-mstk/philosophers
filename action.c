#include "philo.h"

void	reset_deathtime(t_philo *philo)
{
	// pthread_mutex_lock(&philo->philo_mutex);
	philo->last_meal_time = get_time();
	// pthread_mutex_unlock(&philo->philo_mutex);
}

void	take_forks_philo(t_env *env)
{
	pthread_mutex_lock(env->philo->r_forks);
	pthread_mutex_lock(env->philo->l_forks);
	// pthread_mutex_lock(&philo->philo_mutex);
	print_string(env, get_time(), env->philo->num, "has taken a fork");
	// pthread_mutex_unlock(&philo->philo_mutex);
}

void	eating_philo(t_env *env)
{
	// pthread_mutex_lock(&philo->philo_mutex);
	print_string(env, get_time(), env->philo->num, "is eating");
	reset_deathtime(env->philo);
	env->philo->time.num_of_eat--;
	// pthread_mutex_unlock(&philo->philo_mutex);
	usleep(env->philo->time.eat * 1000);
	pthread_mutex_unlock(env->philo->r_forks);
	pthread_mutex_unlock(env->philo->l_forks);
}

void	sleeping_philo(t_env *env)
{
	// pthread_mutex_lock(&philo->philo_mutex);
	print_string(env, get_time(), env->philo->num, "is sleeping");
	// pthread_mutex_unlock(&philo->philo_mutex);
	usleep(env->philo->time.sleep * 1000);
}

void	thinking_philo(t_env *env)
{
	// pthread_mutex_lock(&philo->philo_mutex);
	print_string(env, get_time(), env->philo->num, "is thinking");
	// pthread_mutex_unlock(&philo->philo_mutex);
}