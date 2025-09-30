/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcemon <marcemon@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:43:13 by marcemon          #+#    #+#             */
/*   Updated: 2025/09/30 15:19:51 by marcemon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	put_err_args(int argc)
{
	if (argc < 5)
		return (ft_write("not enough args"));
	return (ft_write("too many args"));
}
