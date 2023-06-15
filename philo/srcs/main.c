/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hagewahi <hagewahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 17:21:09 by mahayase          #+#    #+#             */
/*   Updated: 2023/06/15 10:30:24 by hagewahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_pstr(char *str)
{
    write(1, str, ft_strlen(str));
}

static void    print_header(void)
{
    ft_pstr("  ________  ___  ___  ___  ___       ________      \n");
    ft_pstr(" |\\   __  \\|\\  \\|\\  \\|\\  \\|\\  \\     |\\   __  \\     \n");
    ft_pstr(" \\ \\  \\|\\  \\ \\  \\\\\\  \\ \\  \\ \\  \\    \\ \\  \\|\\  \\    \n");
    ft_pstr("  \\ \\   ____\\ \\   __  \\ \\  \\ \\  \\    \\ \\  \\\\\\  \\   \n");
    ft_pstr("   \\ \\  \\___|\\ \\  \\ \\  \\ \\  \\ \\  \\____\\ \\  \\\\\\  \\  \n");
    ft_pstr("    \\ \\__\\    \\ \\__\\ \\__\\ \\__\\ \\_______\\ \\_______\\ \n");
    ft_pstr("     \\|__|     \\|__|\\|__|\\|__|\\|_______|\\|_______| \n");
}

void	init_philos(t_philo *philos, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philo)
	{
		init_philo(&philos[i], info, i);
		i++;
	}
}

void	start_threads(t_env *env, t_philo *philo, t_info *info)
{
	int	i;
	int	ret;

	i = 0;
	info->start_time = get_time();
	while (i < info->num_of_philo)
	{
		env[i].info = info;
		env[i].philo = &philo[i];
		ret = pthread_create(&philo[i].thread_id, NULL, (void *)philo_routine, &env[i]);
		if (ret != 0)
			exit(1);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_env		*env;
	t_philo	*philo;
	t_info	*info;

	print_header();
	if (ac != 5 && ac != 6)
		return (0);
	info = init_info(ac, av); 
	info->forks = init_forks(info->num_of_philo);
	philo = (t_philo *)malloc(sizeof(t_philo) * info->num_of_philo);
	init_philos(philo, info);
	env = (t_env *)malloc(sizeof(t_env) * info->num_of_philo);
	start_threads(env, philo, info);
	superwatchman(env, info);
	free(philo);
	destroy_forks(info);
	free(info->forks);
	free(info);
	free(env);
	return (0);
}
