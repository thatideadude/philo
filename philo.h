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

typedef struct	s_philo
{
	int		id;
	int		meals;
	int 	last_meal;
}	t_philo;



typedef	struct s_ref
{
	struct timeval	start_time;
	int	time_to_die;
	int time_to_eat;
	int	time_to_sleep;
	int	rounds;
}	t_ref;
	
// VALIDATE
int		has_valid_args(char *argv1, char *argv2, char *argv3, char *argv4);

// MAKE
t_philo	**make_players(int amount);
t_ref	*make_referee(int ms_die, int ms_eat, int ms_sleep);

// SIMULATE
void	start_sim(t_philo **players, t_ref *referee);

// HELP
int		ft_atoi(char *str);
int		ft_space(char c);
int		put_err_args(int argc);
int		ft_write(char *str);
void	exit_sim(t_philo **players, t_ref *referee, int amount);
int		is_valid_int(char *str);

#endif
