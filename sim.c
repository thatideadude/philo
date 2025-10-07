#include	"philo.h"

void	feed_philo(t_ref *referee)
{
	int	i;
	int iter;
	int other_fork;

	i = 0;
	ft_write("routine started\n");
	while (i < referee->amount)
	{
		other_fork = i + 1;
		if (other_fork >= referee->amount)
			other_fork = 0;
		iter = i;
		while (referee->current_round % 2 == i % 2 && i < referee->amount)
		{
			pthread_mutex_init(referee->forks[i], NULL);
			pthread_mutex_init(referee->forks[other_fork], NULL);
			pthread_mutex_lock(referee->forks[i]);
			pthread_mutex_lock(referee->forks[other_fork]);
			printf("%d is eating\n", i);
			i += 2;
		}
		i = iter;
		while (referee->current_round % 2 == i % 2 && i < referee->amount)
		{
			usleep(1000000);
			pthread_mutex_unlock(referee->forks[i]);
			pthread_mutex_unlock(referee->forks[other_fork]);
			pthread_mutex_destroy(referee->forks[i]);
			pthread_mutex_destroy(referee->forks[other_fork]);
			printf("%d finished eating\n", i);
			i += 2;
		}
		i = iter;
		++i;
	}
	referee->current_round++;
}

int		is_gameover(t_ref *referee)
{
	(void) referee;
	return (0);
}

void	*start_routine(void *referee)
{
	if (!is_gameover(referee))
	{
		feed_philo((t_ref *)referee);
	}
	return (NULL);
}

void	*create_thread(t_ref *referee)
{
	pthread_t *thread;

	thread = malloc(sizeof(pthread_t *));
	pthread_create(thread, NULL, start_routine, (void *)referee);
	ft_write("thread created\n");
	return (thread);
}


void	start_simulation(t_ref *referee)
{
	int	i;

	i = -1;
	while (1)
	{
		while (++i < referee->amount)
		{
			referee->players[i]->thread = create_thread(referee);
			pthread_join(referee->players[i]->thread[0], NULL);
		}
		i = -1;
	}
}
