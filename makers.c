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
