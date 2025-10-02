/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcemon <marcemon@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:40:51 by marcemon          #+#    #+#             */
/*   Updated: 2025/09/30 15:21:00 by marcemon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo**	players;
	t_ref		*referee;
	int			i;
	struct timeval	current;

	if (argc < 5 || argc > 6 || !has_valid_args(argv[1], argv[2], argv[3], argv[4]))
		return (put_err_args(argc));
	players = make_players(ft_atoi(argv[1]));
	referee = make_referee(ft_atoi(argv[2]), ft_atoi(argv[3]), ft_atoi(argv[4]));
	// start_sim(players, referee);
	exit_sim(players, referee, ft_atoi(argv[1]));
	return (0);
}
