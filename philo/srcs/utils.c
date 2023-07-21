/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahayase <mahayase@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:56:12 by hagewahi          #+#    #+#             */
/*   Updated: 2023/07/21 15:14:12 by mahayase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

void	print_string(t_env *env, unsigned long time, int num, char *str)
{
	pthread_mutex_lock(&env->info->print_mutex);
	if (env->info->print_flag)
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
	int		i;
	int		sign;
	long	num;

	i = 0;
	sign = 1;
	num = 0;
	while (str[i] && (str[i] == ' ' || (9 <= str[i] && str[i] <= 13)))
		i++;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
		if (str[i++] == '-')
			sign *= -1;
	while (str[i] && ft_isdigit(str[i]))
	{
		if (sign == -1 && (num > LONG_MAX / 10 || \
						(num == LONG_MAX / 10 && \
						str[i] - '0' - 1 > LONG_MAX % 10)))
			return ((int)LONG_MIN);
		if (sign == 1 && (num > LONG_MAX / 10 || \
						(num == LONG_MAX / 10 && \
						str[i] - '0' > LONG_MAX % 10)))
			return ((int)LONG_MAX);
		num = num * 10 + (str[i++] - '0');
	}
	return ((int)(num * sign));
}
