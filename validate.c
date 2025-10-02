#include "philo.h"

int	is_valid_int(char *str)
{
	while (ft_space(*str))
		str++;
	if (*str == '-')
		return (0);
	if (*str == '+')
		str++;
	if (!*str)
		return(1);
	while (*str >= '0' && *str <= '9')
		str++;
	if (*str)
		return (0);
	return (1);
}

int	has_valid_args(char *argv1, char *argv2, char *argv3, char *argv4)
{
	if (!is_valid_int(argv1) || !is_valid_int(argv2))
		return (0);
	if (!is_valid_int(argv3) || !is_valid_int(argv4))
		return (0);
	return (1);
}
