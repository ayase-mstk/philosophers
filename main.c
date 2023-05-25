/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahayase <mahayase@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 17:21:09 by mahayase          #+#    #+#             */
/*   Updated: 2023/05/25 18:33:32 by mahayase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	main(int ac, char **av)
{
	int number_of_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_of_times_each_philosopher_must_eat;
	pthread_attr_t ()tattr;
	pthread_t tid;
	extern void *start_routine(void *arg);
	void *arg;
	int	ret;
	int	status;

	ret = pthread_attr_init(&tattr);
	ret = pthread_create(&tid, &tattr, start_routine, arg);

	

	// pthred_mutex_lock(&forks);
	// pthred_mutex_unlock(&forks);
	return (0);
}
