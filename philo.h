/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   makers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcemon <marcemon@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 08:56:37 by marcemon          #+#    #+#             */
/*   Updated: 2025/06/01 08:56:37 by marcemon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
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
void	cleanup_board(t_board *b, int i);

#endif
