#include "philo_bonus.h"
#include <limits.h>

unsigned long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_string(t_env *env, unsigned long time, int num, char *str)
{
	sem_wait(env->write);
	printf("%lu %d %s\n", time - env->start_time, num, str);
	sem_post(env->write);
}

void	exit_error(char *str)
{
	printf("Error: %s\n", str);
	exit(EXIT_FAILURE);
}

static int	ft_isdigit(int c)
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