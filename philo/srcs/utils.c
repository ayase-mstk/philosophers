/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hagewahi <hagewahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:56:12 by hagewahi          #+#    #+#             */
/*   Updated: 2023/06/15 10:28:37 by hagewahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
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
