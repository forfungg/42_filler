/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strat_adjust2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 18:14:41 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/11 19:15:01 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	l_search_area(t_map *map, t_coords *start, t_coords *d, char side)
{
	int			change;

	change = l_search_area2(map, start, d, side);
	if (!change)
	{
		map->left.crit.x = map->left.i.x < 0 ? map->left.i.x + 1 :\
			map->left.i.x - 1;
		map->left.crit.y = map->left.i.y < 0 ? map->left.i.y + 1 :\
			map->left.i.y - 1;
		map->left.cr = angle_ratio(&(map->left.edge), &(map->left.crit), side);
		d->x *= -1;
		d->y *= -1;
		l_search_area(map, &(map->left.crit), d, 'w');
	}
}

double	angle_ratio(t_coords *a, t_coords *b, char side)
{
	double d_x;
	double d_y;

	d_x = (double)abs_val(a->x - b->x);
	d_y = (double)abs_val(a->y - b->y);
	if (side == 'r')
		return (d_x != 0 ? d_y / d_x : 0);
	else
		return (d_y != 0 ? d_x / d_y : 0);

}

void	adjust_right_crit(t_map *map)
{
	t_coords	d;
	t_coords	i;

	d.x = map->main_v.direction.x > 0 ? -1 : 1;
	d.y = map->main_v.direction.y > 0 ? -1 : 1;
	i.x = map->right.edge.x;
	i.y = map->right.edge.y;
	if ((d.x > 0 && d.y < 0) || (d.x < 0 && d.y > 0))
	{
		while (0 < i.x && i.x < map->columns - 1)
		{
			i.x += d.x;
			if (IS_ENEMY(map->map[i.y][i.x]))
			{
				d.x *= -1;
				d.y *= -1;
				r_search_area(map, &i, &d, 'r');
				return ;
			}
		}
	}
	else
	{
		while (0 < i.y && i.y < map->lines - 1)
		{
			i.y += d.y;
			if (IS_ENEMY(map->map[i.y][i.x]))
			{
				d.x *= -1;
				d.y *= -1;
				r_search_area(map, &i, &d, 'r');
				return ;
			}
		}
	}
	i.x = map->right.edge.x;
	i.y = map->right.edge.y;
	r_search_area(map, &i, &d, 'l');
}

void	r_search_area(t_map *map, t_coords *start, t_coords *d, char side)
{
	t_coords	i;
	int			change;

	change = 0;
	i.y = start->y;
	while (-1 < i.y && i.y < map->lines)
	{
		i.x = start->x;
		while (-1 < i.x && i.x < map->columns)
		{
			if (IS_ENEMY(map->map[i.y][i.x]))
			{
				change = 1;
				if (map->right.cr > angle_ratio(&(map->right.edge), &i, side == 'w' ? 'l' : side) || map->right.cr == 0 || side == 'w')
				{
					map->right.crit = i;
					map->right.cr = angle_ratio(&(map->right.edge), &i, side == 'w' ? 'l' : side);
					if (side == 'w')
						return ;
					start->x = i.x;
					start->y = i.y;
				}
			}
			i.x += d->x;
		}
		i.y += d->y;
	}
	if (!change)
	{
		map->right.crit.x = i.x < 0 ? i.x + 1 : i.x - 1;
		map->right.crit.y = i.y < 0 ? i.y + 1 : i.y - 1;
		map->right.cr = angle_ratio(&(map->right.edge), &(map->right.crit), side);
		d->x *= -1;
		d->y *= -1;
		r_search_area(map, &(map->right.crit), d, 'w');
	}
}
