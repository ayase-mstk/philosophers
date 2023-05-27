#include "philo.h"

void	reset_borntime(t_philo *philo)
{
	struct timeval tv;

	// pthread_mutex_lock(&philo->philo_mutex);
	gettimeofday(&tv, NULL);
	philo->borntime = tv.tv_usec;
	// pthread_mutex_unlock(&philo->philo_mutex);
}

void	take_forks_philo(t_philo *philo)
{
	struct timeval tv;

	pthread_mutex_lock(philo->r_forks);
	pthread_mutex_lock(philo->l_forks);
	pthread_mutex_lock(&philo->philo_mutex);
	gettimeofday(&tv, NULL);
	printf("%ld %d has taken a fork\n", tv.tv_usec ,philo->num);
	pthread_mutex_unlock(&philo->philo_mutex);
}

void	eating_philo(t_philo *philo)
{
	struct timeval tv;

	pthread_mutex_lock(&philo->philo_mutex);
	gettimeofday(&tv, NULL);
	printf("%ld %d is eating\n", tv.tv_usec ,philo->num);
	reset_borntime(philo);
	philo->time.num_of_eat--;
	pthread_mutex_unlock(&philo->philo_mutex);
	usleep(philo->time.eat * 1000);
	pthread_mutex_unlock(philo->r_forks);
	pthread_mutex_unlock(philo->l_forks);
}

void	sleeping_philo(t_philo *philo)
{
	struct timeval tv;

	pthread_mutex_lock(&philo->philo_mutex);
	gettimeofday(&tv, NULL);
	printf("%ld %d is sleeping\n", tv.tv_usec ,philo->num);
	pthread_mutex_unlock(&philo->philo_mutex);
	usleep(philo->time.sleep * 1000);
}

void	thinking_philo(t_philo *philo)
{
	struct timeval tv;

	pthread_mutex_lock(&philo->philo_mutex);
	gettimeofday(&tv, NULL);
	printf("%ld %d is thinking\n", tv.tv_usec ,philo->num);
	pthread_mutex_unlock(&philo->philo_mutex);
}