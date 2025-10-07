#include "philo.h"

void	*local_malloc(char *str, int size)
{
	static int i = 0;
	void	*mem;
	
	mem = malloc(size);
	printf("call %d from %s\n", i++, str);
	return (mem);
}

t_philo	**make_players(int amount)
{
	t_philo	*philo;
	t_philo	**group;
	int		i;

	philo = local_malloc("line 16\n", sizeof(t_philo) * amount);
	group = local_malloc("line 17\n", sizeof(t_philo *) * amount);
	if (!philo || !group)
		return (ft_write("Malloc error./n"), NULL);
	i = 0;
	while (i < amount)
	{
		group[i] = &philo[i];
		philo[i].id = i + 1;
		philo[i].last_meal = 0;
		++i;
	}
	return (group);
};

t_ref	*make_referee(int ms_die, int ms_eat, int ms_sleep, int amount)
{
	t_ref			*referee;
	pthread_mutex_t	*mutex;	
	pthread_mutex_t	**group;
	int				i;
	
	referee = local_malloc("line 36\n", sizeof(t_ref));
	if (!referee)
		return (ft_write("Malloc error referee"), NULL);
	mutex = local_malloc("line 44\n", sizeof(pthread_mutex_t) * amount);
	group = local_malloc("line 40\n", sizeof(pthread_mutex_t *) * amount);
	i = -1;
	while (++i < amount)
		group[i] = &mutex[i];
	referee->forks = &group[0];
	if (!referee->forks)
		return (ft_write("Malloc error forks"), NULL);
	//gettimeofday(&referee->start_time, 0);
	referee->players = make_players(amount);
	referee->amount = amount;
	referee->current_round = 0;
	referee->time_to_die = ms_die;
	referee->time_to_eat = ms_eat;
	referee->time_to_eat = ms_sleep;
	return (referee);
};
