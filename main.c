#include "philo.h"

int main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (put_err_args(argc));
	return (0);
}
