#include	"philo.h"

long	ms_difference(struct timeval *start, struct timeval *now)
{
	long seconds;
	long microseconds;
	long difference;

	seconds = now->tv_sec - start->tv_sec;
	microseconds = now->tv_usec - start->tv_usec;
	if (microseconds < 0)
	{
		microseconds += 1000000;
		seconds -= 1;
	}
	difference = seconds * 1000000 + microseconds;
	return (difference / 1000);
}

long	tv_to_ms(struct timeval *tv)
{
	long	seconds;
	long	microseconds;
	long	total_ms;

	seconds = tv->tv_sec * 10000000;
	microseconds = tv->tv_usec;
	total_ms = (seconds + microseconds) / 1000;
	return (total_ms);
}

void	ft_sleep(int time_ms)
{
	struct timeval	before;
	struct timeval	after;

	gettimeofday(&before, 0);
	usleep(time_ms * 1000);
	gettimeofday(&after, 0);
	printf("SLEPT FOR %ld ms\n", ms_difference(&before, &after));
}

int	should_put_down_right_fork(t_ref *referee, int id, int right_fork)
{
	return (referee->players[id]->is_eating == 2 && referee->players[right_fork]->is_eating == 2);
}

int	should_put_down_own_fork(t_ref *referee, int id)
{
	return (referee->players[id]->is_eating == 2);
}

void	put_forks_down(t_ref *referee, int id, int left_fork)
{
	//pthread_mutex_t	mutex;

	//pthread_mutex_init(&mutex, NULL);
	//pthread_mutex_lock(&mutex);
	referee->players[id]->is_eating = 0;
	referee->players[left_fork]->is_eating = 0;
	//printf("%d finished eating.\n", id); 
	//printf("%d put down fork %d\n", id, fork);
	pthread_mutex_unlock(referee->forks[id]);
	pthread_mutex_unlock(referee->forks[left_fork]);
	//pthread_mutex_unlock(&mutex);
	//pthread_mutex_destroy(&mutex);
}

int	are_both_forks_free(t_ref *referee, int left_fork, int right_fork)
{
	return (referee->players[left_fork]->is_eating == 0 && referee->players[right_fork]->is_eating == 0);
}

void	eat(t_ref *referee, int left_fork, int right_fork)
{
	//pthread_mutex_t	mutex;

	//pthread_mutex_init(&mutex, NULL);
	//pthread_mutex_lock(&mutex);
	struct timeval	current_time;
	long			time;

	referee->players[left_fork]->is_eating = 2;
	referee->players[right_fork]->is_eating = 2;
	if (referee->players[left_fork]->is_eating == 0)
		pthread_mutex_lock(referee->forks[left_fork]);
	if (referee->players[right_fork]->is_eating == 0)
		pthread_mutex_lock(referee->forks[right_fork]);
	gettimeofday(&current_time, 0);
	referee->players[left_fork]->last_meal = current_time;
	time = ms_difference(&referee->start_time, &current_time);
	ft_putnbr(time);
	printf("ms player %d is eating\n", left_fork);
	ft_sleep(referee->time_to_eat);
	//pthread_mutex_unlock(&mutex);
	//pthread_mutex_destroy(&mutex);
}

int	find_neediest(t_ref *referee)
{
	int	i;
	int	neediest;

	i = -1;
	neediest = 0;
	while (++i < referee->amount)
	{
		if (tv_to_ms(&referee->players[i]->last_meal) < tv_to_ms(&referee->players[neediest]->last_meal)
				&& referee->players[i]->is_eating == 0)
			neediest = i;
	}
	return (neediest);
}

void	feed_philo(t_ref *referee)
{
	int	i;
	int right_fork;
	int neediest;
	int neediest_right;

	neediest = find_neediest(referee);
	neediest_right = neediest + 1;
	if (neediest_right >= referee->amount)
		neediest_right = 0;
	i = -1;
	if (are_both_forks_free(referee, neediest, neediest_right))
	{
		eat(referee, neediest, neediest_right);
		printf("feeding neediest\n");
	}
	while (++i < referee->amount)
	{
		right_fork = i + 1;
		if (right_fork >= referee->amount)
			right_fork = 0;
		if (are_both_forks_free(referee, i, right_fork))
		{
			eat(referee, i, right_fork);
		}
	}
	i = -1;
	while (++i < referee->amount)
	{
		right_fork = i + 1;
		if (right_fork >= referee->amount)
			right_fork = 0;
		if (should_put_down_right_fork(referee, i, right_fork))
			put_forks_down(referee, i, right_fork);
	}
	referee->current_round++;
}


int		is_gameover(t_ref *referee)
{
	int i;
	struct timeval	last_meal;
	struct timeval	current_time;

	i = -1;
	while (++i < referee->amount)
	{
		gettimeofday(&current_time, 0);
		last_meal = referee->players[i]->last_meal;
		ft_putnbr(ms_difference(&last_meal, &current_time));
		printf("\n\nplayer %d last meal was %ld ms ago\n", i, ms_difference(&last_meal, &current_time));
//		printf("START TIME: %ld\n", referee->start_time.tv_usec / 1000);
//		printf("LAST MEAL TIME: %ld\n", referee->players[i]->last_meal.tv_usec / 1000);
//		printf("CURRENT TIME: %ld\n", current_time.tv_usec / 1000);
	//	printf("checking if %d is alive. His last meal was %ld ms ago\n", i, 
	//		current_time.tv_usec - referee->players[i]->last_meal.tv_usec);
		if (ms_difference(&last_meal, &current_time) > referee->time_to_die)
			return (1);
	}
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

	thread = malloc(sizeof(pthread_t));
	pthread_create(thread, NULL, start_routine, (void *)referee);
	//ft_write("thread created\n");
	return (thread);
}


void	start_simulation(t_ref *referee)
{
	int	i;
	while (!is_gameover(referee))
	{
		i = -1;
		while (++i < referee->amount)
		{
			if (is_gameover(referee))
				return ; 
			referee->players[i]->thread = create_thread(referee);
		}
		i = -1;
		while (++i < referee->amount)
		{
			if (is_gameover(referee))
				return ; 
			pthread_join(referee->players[i]->thread[0], NULL);
		}
	}
}
