/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculus_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 10:56:40 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/09 16:29:03 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

long double		dist_direct(t_map *map, t_coords *p)
{
	long double a;
	long double b;
	t_coords	d;
	t_coords	qd;

	qd.x = map->main_v.direction.x > 0 ? 1 : -1;
	qd.y = map->main_v.direction.y > 0 ? 1 : -1;
	if (p->x == map->main_v.start.x && p->y == map->main_v.start.y)
		return ((long double)0);
	a = ft_m_dist(&(map->main_v.start), p);
	b = ft_sqrt_prec(a * a * 2, 5) / 2;
	d.x = map->main_v.start.x - p->x > 0 ? 1 : -1;
	d.y = map->main_v.start.y - p->y > 0 ? 1 : -1;
	if (qd.x == d.x && qd.y == d.y)
		return (ft_sqrt_prec(a * a + b * b, 5));
	else if (qd.x != d.x && qd.y != d.y)
		return (-1 * ft_sqrt_prec(a * a + b * b, 5));
	else
		return (0.5 * ft_sqrt_prec(a * a + b * b, 5));
}

long double		ft_m_dist(const t_coords *a, const t_coords *b)
{
	int i;
	int k;

	if (a == b)
		return (0);
	i = a->x - b->x;
	k = a->y - b->y;
	return (ft_sqrt_prec(i * i + k * k, 5));
}

void			ft_middle(t_map *map, t_coords *center)
{
	center->x = map->columns / 2;
	center->y = map->lines / 2;
}
