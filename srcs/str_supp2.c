/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_supp2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 18:45:45 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/11 19:28:57 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		lsa(t_map *map, t_coords *start, t_coords *i, char s)
{
	map->left.crit = *i;
	map->left.cr = angle_ratio(&(map->left.edge), i, s == 'w' ? 'r' : s);
	if (s == 'w')
		return (1);
	start->x = i->x;
	start->y = i->y;
	return (0);
}

int		l_search_area2(t_map *map, t_coords *start, t_coords *d, char s)
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
				if (map->left.cr > angle_ratio(&(map->left.edge), &i,\
					s == 'w' ? 'r' : s) || map->left.cr == 0 || s == 'w')
					if (lsa(map, start, &i, s))
						return (1);
			}
			i.x += d->x;
		}
		i.y += d->y;
	}
	map->left.i = i;
	return (change);
}

int		rsa(t_map *map, t_coords *start, t_coords *i, char s)
{
	map->right.crit = *i;
	map->right.cr = angle_ratio(&(map->right.edge), i, s == 'w' ? 'l' : s);
	if (s == 'w')
		return (1);
	start->x = i->x;
	start->y = i->y;
	return (0);
}

int		r_search_area2(t_map *map, t_coords *start, t_coords *d, char s)
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
				if (map->right.cr > angle_ratio(&(map->right.edge), &i,\
					s == 'w' ? 'l' : s) || map->right.cr == 0 || s == 'w')
					if (rsa(map, start, &i, s))
						return (1);
			}
			i.x += d->x;
		}
		i.y += d->y;
	}
	map->right.i = i;
	return (change);
}
