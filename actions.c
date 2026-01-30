#include "philo.h"

long	get_t(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_putnbr(int n)
{
	long	nb;
	char	c;

	nb = n;
	if (nb < 0)
	{
		write(1, "-", 1);
		nb *= -1;
	}
	if (nb > 9)
		ft_putnbr(nb / 10);
	c = (nb % 10) + '0';
	write(1, &c, 1);
}

int	ft_sleep(int time_ms, t_philo *p)
{
	long	start;

	start = get_t();
	while (get_t() - start < time_ms)
	{
		if (!all_ok(p->board))
			return (1);
		usleep(100);
	}
	return (0);
}

int	die(t_philo *player)
{
	pthread_mutex_lock(&player->board->death);
	if (player->board->is_dead_flag)
	{
		pthread_mutex_unlock(&player->board->death);
		return (1);
	}
	player->board->is_dead_flag = 1;
	pthread_mutex_unlock(&player->board->death);
	pthread_mutex_lock(&player->board->terminal);
	ft_putnbr(get_t() - player->start_time);
	write(1, " ", 1);
	ft_putnbr(player->id + 1);
	write(1, " has died\n", 10);
	pthread_mutex_unlock(&player->board->terminal);
	return (1);
}

int	ft_atoi(char *str)
{
	int	res;

	res = 0;
	while (*str >= '0' && *str <= '9')
		res = res * 10 + (*str++ - '0');
	return (res);
}
