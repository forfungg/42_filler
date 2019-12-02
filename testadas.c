#include <stdio.h>
#include <stdlib.h>

long double	ft_sqrt_prec(long double nb, int prec);

int main (int ac, char **av)
{
	long double nb;
	int p;
	long double res;

	if (ac == 3)
	{
		nb = (long double)atoi(av[1]);
		p = atoi(av[2]);
		res = ft_sqrt_prec(nb, p);
		printf("sqrt of %.3Lf with prec(%d) is %.*Lf\n", nb, p, p, res);
	}
	return 0;
}