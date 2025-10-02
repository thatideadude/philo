#include "philo.h"

void	exit_sim(t_philo **players, t_ref *referee, int amount)
{
	if (players[0])
		free(players[0]);
	if (players)
		free(players);
	if (referee)
		free(referee);
}
