/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcemon <marcemon@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:40:51 by marcemon          #+#    #+#             */
/*   Updated: 2025/09/30 15:21:00 by marcemon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

typedef struct	s_philo
{
	int				id;
	int				meals;
	struct timeval	last_meal;
	int				is_eating;
	pthread_t		*thread;
}	t_philo;

typedef	struct s_ref
{
	t_philo			**players;
	struct timeval	start_time;
	struct timeval	current_time;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				rounds;
	int				amount;
	int				current_round;
	pthread_mutex_t	**forks;
}	t_ref;
	
// VALIDATE
int		has_valid_args(char *argv1, char *argv2, char *argv3, char *argv4);

// MAKE
t_philo	**make_players(t_ref *referee, int amount);
t_ref	*make_referee(int ms_die, int ms_eat, int ms_sleep, int amount);

// SIMULATE
void	start_simulation(t_ref *referee);

// HELP
void	ft_putnbr(int nb);
int		ft_atoi(char *str);
int		ft_space(char c);
int		put_err_args(int argc);
int		ft_write(char *str);
void	exit_sim(t_ref *referee);
int		is_valid_int(char *str);
long	tv_to_ms(struct timeval *tv);

#endif
