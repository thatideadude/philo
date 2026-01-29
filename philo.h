#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

struct	s_philo;
struct	s_board;

typedef struct s_board t_board;
typedef struct s_philo t_philo;

struct	s_board
{
	pthread_mutex_t	**forks;
	pthread_mutex_t	action;
	pthread_mutex_t	death;
	pthread_mutex_t	meal;
	t_philo		**players;
	pthread_mutex_t	terminal;
	struct timeval	start_time;
};

struct	s_philo
{
	int				id;
	int				meals;
	int				sleeps;
	struct timeval 	last_meal;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				is_dead;
	struct timeval	start_time;
	pthread_t		thread;
	t_board			*board;
};

#endif
