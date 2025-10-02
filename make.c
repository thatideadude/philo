#include "philo.h"

t_philo	**make_players(int amount)
{
	t_philo	*philo;
	t_philo	**group;
	int		i;

	philo = malloc(sizeof(t_philo) * amount);
	group = malloc(sizeof(t_philo *) * amount);
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

t_ref	*make_referee(int ms_die, int ms_eat, int ms_sleep)
{
	t_ref			*referee;
	
	referee = malloc(sizeof(t_ref));
	if (!referee)
		return (ft_write("Malloc error"), NULL);
	gettimeofday(&referee->start_time, NULL);
	referee->time_to_die = ms_die;
	referee->time_to_eat = ms_eat;
	referee->time_to_eat = ms_sleep;
	return (referee);
};
