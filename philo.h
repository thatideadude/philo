#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

struct	s_board;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	long			start_time;
	long			last_meal;
	int				meals;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	struct s_board	*board;
}	t_philo;

typedef struct s_board
{
	int				num_philos;
	int				is_dead_flag;
	int				meals_limit;
	long			start_time;
	t_philo			**players;
	pthread_mutex_t	**forks;
	pthread_mutex_t	meal;
	pthread_mutex_t	death;
	pthread_mutex_t	terminal;
}	t_board;

long	get_t(void);
void	ft_putnbr(int n);
int		ft_atoi(char *str);
void	start_board(t_board *board, char **argv);
int		all_ok(t_board *board);
int		ft_putstr(t_philo *player, char *str);
int		die(t_philo *player);
int		ft_sleep(int time_ms, t_philo *player);
void	*start_routine(void *arg);
void	make_players(int i, t_board	*b, char **argv);

#endif
