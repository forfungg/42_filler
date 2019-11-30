#include <stdio.h>

typedef struct	s_coords
{
	int	x;
	int	y;
}				t_coords;

int main()
{
	t_coords p1;
	t_coords p2;
	t_coords p3;

	p1.x = 10;
	p1.y = 20;
	p2.x = 7;
	p2.y = 17;
	p3 = p1 - 3;
	printf("%d %d", p2.x, p2.y);
	return 0;
}