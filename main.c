#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	long			last_eat;
	int				meals;
	pthread_t		thread;
	pthread_mutex_t	*f1;
	pthread_mutex_t	*f2;
	pthread_mutex_t	lock;
	t_data			*d;
}	t_philo;

struct s_data
{
	int				num;
	int				die;
	int				eat;
	int				sleep;
	int				must;
	long			start;
	int				stop;
	pthread_mutex_t	write_m;
	pthread_mutex_t	m_lock;
	t_philo			*ph;
	pthread_mutex_t	*forks;
};

long	get_t(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	p_status(t_philo *p, char *s)
{
	pthread_mutex_lock(&p->d->m_lock);
	if (!p->d->stop)
	{
		pthread_mutex_lock(&p->d->write_m);
		printf("%ld %d %s\n", get_t() - p->d->start, p->id, s);
		pthread_mutex_unlock(&p->d->write_m);
	}
	pthread_mutex_unlock(&p->d->m_lock);
}

void	ft_sleep(long ms, t_data *d)
{
	long	start;

	start = get_t();
	while (1)
	{
		pthread_mutex_lock(&d->m_lock);
		if (d->stop)
		{
			pthread_mutex_unlock(&d->m_lock);
			return ;
		}
		pthread_mutex_unlock(&d->m_lock);
		if (get_t() - start >= ms)
			break ;
		usleep(100);
	}
}

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->id % 2 == 0)
		ft_sleep(p->d->eat, p->d);
	while (1)
	{
		pthread_mutex_lock(p->f1);
		p_status(p, "has taken a fork");
		if (p->d->num == 1)
			return (ft_sleep(p->d->die, p->d), pthread_mutex_unlock(p->f1), NULL);
		pthread_mutex_lock(p->f2);
		p_status(p, "has taken a fork");
		pthread_mutex_lock(&p->lock);
		p->last_eat = get_t();
		p->meals++;
		pthread_mutex_unlock(&p->lock);
		p_status(p, "is eating");
		ft_sleep(p->d->eat, p->d);
		pthread_mutex_unlock(p->f2);
		pthread_mutex_unlock(p->f1);
		pthread_mutex_lock(&p->d->m_lock);
		if (p->d->stop || (p->d->must != -1 && p->meals >= p->d->must))
			return (pthread_mutex_unlock(&p->d->m_lock), NULL);
		pthread_mutex_unlock(&p->d->m_lock);
		p_status(p, "is sleeping");
		ft_sleep(p->d->sleep, p->d);
		p_status(p, "is thinking");
		if (p->d->num % 2)
			ft_sleep((p->d->eat * 2) - p->d->sleep, p->d);
	}
}

void	monitor(t_data *d)
{
	int	i;
	int	full;

	while (1)
	{
		full = 0;
		i = -1;
		while (++i < d->num)
		{
			pthread_mutex_lock(&d->ph[i].lock);
			if (get_t() - d->ph[i].last_eat >= d->die)
			{
				p_status(&d->ph[i], "died");
				pthread_mutex_lock(&d->m_lock);
				d->stop = 1;
				pthread_mutex_unlock(&d->m_lock);
				return ((void)pthread_mutex_unlock(&d->ph[i].lock));
			}
			if (d->must != -1 && d->ph[i].meals >= d->must)
				full++;
			pthread_mutex_unlock(&d->ph[i].lock);
		}
		if (d->must != -1 && full == d->num)
		{
			pthread_mutex_lock(&d->m_lock);
			d->stop = 1;
			return ((void)pthread_mutex_unlock(&d->m_lock));
		}
		usleep(500);
	}
}

int	main(int ac, char **av)
{
	t_data	d;
	int		i;

	if (ac < 5 || ac > 6)
		return (1);
	d.num = atoi(av[1]); d.die = atoi(av[2]); d.eat = atoi(av[3]);
	d.sleep = atoi(av[4]); d.must = (ac == 6) ? atoi(av[5]) : -1;
	d.stop = 0; d.start = get_t();
	d.ph = malloc(sizeof(t_philo) * d.num);
	d.forks = malloc(sizeof(pthread_mutex_t) * d.num);
	pthread_mutex_init(&d.write_m, NULL);
	pthread_mutex_init(&d.m_lock, NULL);
	i = -1;
	while (++i < d.num)
	{
		pthread_mutex_init(&d.forks[i], NULL);
		pthread_mutex_init(&d.ph[i].lock, NULL);
		d.ph[i].id = i + 1; d.ph[i].last_eat = d.start;
		d.ph[i].meals = 0; d.ph[i].d = &d;
		d.ph[i].f1 = &d.forks[i];
		d.ph[i].f2 = &d.forks[(i + 1) % d.num];
		if (d.ph[i].id % 2 == 0)
		{
			d.ph[i].f1 = &d.forks[(i + 1) % d.num];
			d.ph[i].f2 = &d.forks[i];
		}
		pthread_create(&d.ph[i].thread, NULL, routine, &d.ph[i]);
	}
	monitor(&d);
	i = -1;
	while (++i < d.num)
		pthread_join(d.ph[i].thread, NULL);
	i = -1;
	while (++i < d.num)
	{
		pthread_mutex_destroy(&d.forks[i]);
		pthread_mutex_destroy(&d.ph[i].lock);
	}
	pthread_mutex_destroy(&d.write_m);
	pthread_mutex_destroy(&d.m_lock);
	return (free(d.ph), free(d.forks), 0);
}
