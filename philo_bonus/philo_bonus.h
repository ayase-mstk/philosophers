#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

typedef struct s_philo
{
	int				id;
	int				nb_eat;
	unsigned long	last_eat;
	pid_t			pid;
}	t_philo;

typedef struct s_env
{
	sem_t			*forks;
	sem_t			*write;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	unsigned long	start_time;
	
}	t_env;

#endif