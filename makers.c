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

void	make_players(int i, t_board	*b, char **argv)
{
	while (++i < b->num_philos)
	{
		b->players[i] = malloc(sizeof(t_philo));
		b->players[i]->id = i;
		b->players[i]->start_time = b->start_time;
		b->players[i]->last_meal = b->start_time;
		b->players[i]->meals = 0;
		b->players[i]->time_to_die = ft_atoi(argv[2]);
		b->players[i]->time_to_eat = ft_atoi(argv[3]);
		b->players[i]->time_to_sleep = ft_atoi(argv[4]);
		b->players[i]->board = b;
		pthread_create(&b->players[i]->thread, NULL,
			start_routine, b->players[i]);
	}
}

void	cleanup_board(t_board *b, int i)
{
	if (b->forks)
	{
		while (++i < b->num_philos)
		{
			if (b->forks[i])
			{
				pthread_mutex_destroy(b->forks[i]);
				free(b->forks[i]);
			}
		}
		free(b->forks);
	}
	if (b->players)
	{
		i = -1;
		while (++i < b->num_philos)
		{
			if (b->players[i])
				free(b->players[i]);
		}
		free(b->players);
	}
	pthread_mutex_destroy(&b->meal);
	pthread_mutex_destroy(&b->death);
	pthread_mutex_destroy(&b->terminal);
}
