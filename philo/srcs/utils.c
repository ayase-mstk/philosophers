/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahayase <mahayase@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:56:12 by hagewahi          #+#    #+#             */
/*   Updated: 2023/06/15 18:09:00 by mahayase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

void	print_string(t_env *env, unsigned long time, int num, char *str)
{
	pthread_mutex_lock(&env->info->print_mutex);
	printf("%ld %d %s\n", (time - env->info->start_time), num, str);
	pthread_mutex_unlock(&env->info->print_mutex);
}

unsigned long	get_time(void)
{
	struct timeval	tv;
	unsigned long	msec;

	gettimeofday(&tv, NULL);
	msec = tv.tv_sec * (unsigned long)1000 + tv.tv_usec / 1000;
	return (msec);
}

void	destroy_forks(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philo)
	{
		pthread_mutex_destroy(&info->forks[i]);
		i++;
	}
}

int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

int	ft_atoi(const char *str)
{
	int			minus;
	long int	ans;

	minus = 1;
	ans = 0;
	while (*str == ' ' || (9 <= (int)*str && (int)*str <= 13))
		str++;
	if (*str == '-')
		minus = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (ft_isdigit(*str))
	{
		if (minus == -1 && (ans > LONG_MAX / 10 || \
						(ans == LONG_MAX / 10 && *str - '0' > LONG_MAX % 10)))
			return ((int)LONG_MIN);
		if (minus == 1 && (ans > LONG_MAX / 10 || \
						(ans == LONG_MAX / 10 && *str - '0' > LONG_MAX % 10)))
			return ((int)LONG_MAX);
		ans = ans * 10 + (*str - '0');
		str++;
	}
	return ((int)(ans * minus));
}
