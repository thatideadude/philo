#include "philo.h"

void	start_board(t_board *b, char **argv)
{
	b->num_philos = ft_atoi(argv[1]);
	b->is_dead_flag = 0;
	b->meals_limit = -1;
}

int	all_ok(t_board *board)
{
	int	res;

	pthread_mutex_lock(&board->death);
	res = (board->is_dead_flag == 0);
	pthread_mutex_unlock(&board->death);
	return (res);
}

int	ft_putstr(t_philo *player, char *str)
{
	pthread_mutex_lock(&player->board->death);
	if (player->board->is_dead_flag)
	{
		pthread_mutex_unlock(&player->board->death);
		return (1);
	}
	pthread_mutex_unlock(&player->board->death);
	pthread_mutex_lock(&player->board->terminal);
	ft_putnbr(get_t() - player->start_time);
	write(1, " ", 1);
	ft_putnbr(player->id + 1);
	write(1, " ", 1);
	while (*str)
		write(1, str++, 1);
	write(1, "\n", 1);
	pthread_mutex_unlock(&player->board->terminal);
	return (0);
}

static void	eat_routine(t_philo *p)
{
	int	f;
	int	s;

	f = p->id;
	s = (p->id + 1) % p->board->num_philos;
	pthread_mutex_lock(p->board->forks[f]);
	ft_putstr(p, "has taken a fork");
	if (p->board->num_philos == 1)
	{
		while (all_ok(p->board))
			usleep(500);
		pthread_mutex_unlock(p->board->forks[f]);
		return ;
	}
	pthread_mutex_lock(p->board->forks[s]);
	ft_putstr(p, "has taken a fork");
	ft_putstr(p, "is eating");
	pthread_mutex_lock(&p->board->meal);
	p->last_meal = get_t();
	p->meals++;
	pthread_mutex_unlock(&p->board->meal);
	ft_sleep(p->time_to_eat, p);
	pthread_mutex_unlock(p->board->forks[f]);
	pthread_mutex_unlock(p->board->forks[s]);
}

void	*start_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->id % 2)
		usleep(1000);
	while (all_ok(p->board))
	{
		eat_routine(p);
		ft_putstr(p, "is sleeping");
		ft_sleep(p->time_to_sleep, p);
		ft_putstr(p, "is thinking");
		if (p->board->num_philos % 2 == 0)
			usleep(500);
		else
			ft_sleep((p->time_to_die - (p->time_to_eat
						+ p->time_to_sleep)) / 2, p);
	}
	return (NULL);
}
