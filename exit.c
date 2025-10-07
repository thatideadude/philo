#include "philo.h"

void	exit_sim(t_ref *referee)
{
	int	i;

	i = 0;
	while (i < referee->amount)
	{
		free(referee->players[i++]->thread);
	}
	if (referee->players[0])
		free(referee->players[0]);
	if (referee->players)
		free(referee->players);
	if (referee->forks)
		free(referee->forks);
	if (referee)
		free(referee);
}
