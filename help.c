/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcemon <marcemon@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:08:14 by marcemon          #+#    #+#             */
/*   Updated: 2025/09/30 15:20:45 by marcemon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	ft_write(char *str)
{
	while (*str)
		write(1, str++, 1);
	return (0);
}

int	ft_space(char c)
{
	return ((c >= 7 && c <= 12) || c == ' ');
}

int	ft_atoi(char *str)
{
	int	res;
	int neg;

	while (str && ft_space(*str))
		str++;
	neg = 0;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg = 1;
		str++;
	}
	res = 0;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	if (neg)
		res *= -1;
	return (res);
}
