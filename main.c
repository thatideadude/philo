#include "philo.h"

static int	is_dead(t_philo *p)
{
	pthread_mutex_lock(&p->board->meal);
	if (get_t() - p->last_meal >= p->time_to_die)
	{
		pthread_mutex_unlock(&p->board->meal);
		die(p);
		return (1);
	}
	pthread_mutex_unlock(&p->board->meal);
	return (0);
}

static int	check_all_full(t_board *b)
{
	int	i;
	int	full_philos;

	i = -1;
	full_philos = 0;
	while (++i < b->num_philos)
	{
		pthread_mutex_lock(&b->meal);
		if (b->players[i]->meals >= b->meals_limit)
			full_philos++;
		pthread_mutex_unlock(&b->meal);
	}
	if (full_philos == b->num_philos)
	{
		pthread_mutex_lock(&b->death);
		b->is_dead_flag = 1;
		pthread_mutex_unlock(&b->death);
		return (1);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_board	*b;
	int		i;

	b = (t_board *)arg;
	while (all_ok(b))
	{
		i = -1;
		while (++i < b->num_philos)
		{
			if (is_dead(b->players[i]))
				return (NULL);
		}
		if (b->meals_limit != -1 && check_all_full(b))
			return (NULL);
		usleep(500);
	}
	return (NULL);
}

static void	init_mutexes(t_board *b)
{
	int	i;

	pthread_mutex_init(&b->meal, NULL);
	pthread_mutex_init(&b->death, NULL);
	pthread_mutex_init(&b->terminal, NULL);
	b->forks = malloc(sizeof(pthread_mutex_t *) * b->num_philos);
	b->players = malloc(sizeof(t_philo *) * b->num_philos);
	i = -1;
	while (++i < b->num_philos)
	{
		b->forks[i] = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(b->forks[i], NULL);
	}
}

int	main(int argc, char **argv)
{
	t_board		b;
	pthread_t	death_monitor;
	int			i;

	if (argc < 5 || argc > 6)
		return (1);
	start_board(&b, argv);
	if (argc == 6)
		b.meals_limit = ft_atoi(argv[5]);
	init_mutexes(&b);
	b.start_time = get_t();
	make_players(-1, &b, argv);
	pthread_create(&death_monitor, NULL, monitor, &b);
	pthread_join(death_monitor, NULL);
	i = -1;
	while (++i < b.num_philos)
		pthread_join(b.players[i]->thread, NULL);
	return (0);
}
