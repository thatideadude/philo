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

#include "philo.h"

static int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->board->meal);
	if (get_t() - philo->last_meal >= philo->time_to_die)
	{
		pthread_mutex_unlock(&philo->board->meal);
		die(philo);
		return (1);
	}
	pthread_mutex_unlock(&philo->board->meal);
	return (0);
}

static int	check_all_full(t_board *board)
{
	int	i;
	int	full_philos;

	i = -1;
	full_philos = 0;
	while (++i < board->num_philos)
	{
		pthread_mutex_lock(&board->meal);
		if (board->players[i]->meals >= board->meals_limit)
			full_philos++;
		pthread_mutex_unlock(&board->meal);
	}
	if (full_philos == board->num_philos)
	{
		pthread_mutex_lock(&board->death);
		board->is_dead_flag = 1;
		pthread_mutex_unlock(&board->death);
		return (1);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_board	*board;
	int		i;

	board = (t_board *)arg;
	while (all_ok(board))
	{
		i = -1;
		while (++i < board->num_philos)
		{
			if (is_dead(board->players[i]))
				return (NULL);
		}
		if (board->meals_limit != -1 && check_all_full(board))
			return (NULL);
		usleep(500);
	}
	return (NULL);
}

static void	init_mutexes(t_board *board)
{
	int	i;

	pthread_mutex_init(&board->meal, NULL);
	pthread_mutex_init(&board->death, NULL);
	pthread_mutex_init(&board->terminal, NULL);
	board->forks = malloc(sizeof(pthread_mutex_t *) * board->num_philos);
	board->players = malloc(sizeof(t_philo *) * board->num_philos);
	i = -1;
	while (++i < board->num_philos)
	{
		board->forks[i] = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(board->forks[i], NULL);
	}
}

int	main(int argc, char **argv)
{
	t_board		board;
	pthread_t	death_monitor;
	int			i;

	if (argc < 5 || argc > 6)
		return (1);
	start_board(&board, argv);
	if (argc == 6)
		board.meals_limit = ft_atoi(argv[5]);
	init_mutexes(&board);
	board.start_time = get_t();
	make_players(-1, &board, argv);
	pthread_create(&death_monitor, NULL, monitor, &board);
	pthread_join(death_monitor, NULL);
	i = -1;
	while (++i < board.num_philos)
		pthread_join(board.players[i]->thread, NULL);
	cleanup_board(&board, -1);
	return (0);
}
