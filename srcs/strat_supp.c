/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strat_supp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 18:34:03 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/11 18:38:46 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		adj_lc_1(t_map *map, t_coords *i, t_coords *d)
{
	while (0 < i->x && i->x < map->columns - 1)
	{
		i->x += d->x;
		if (IS_ENEMY(map->map[i->y][i->x]))
		{
			d->x *= -1;
			d->y *= -1;
			l_search_area(map, i, d, 'l');
			return (1);
		}
	}
	return (0);
}

int		adj_lc_2(t_map *map, t_coords *i, t_coords *d)
{
	while (0 < i->y && i->y < map->lines - 1)
	{
		i->y += d->y;
		if (IS_ENEMY(map->map[i->y][i->x]))
		{
			d->x *= -1;
			d->y *= -1;
			l_search_area(map, i, d, 'l');
			return (1);
		}
	}
	return (0);
}
