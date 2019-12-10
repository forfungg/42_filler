/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strat_adjust.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 18:14:41 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/10 17:26:35 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	adjust_edge(t_map *map, t_token *token, t_coords *p)
{
	anchor_token(token, 0);
	if (ft_m_dist(&(map->left.edge), p) > ft_m_dist(&(map->right.edge), p))
		adjust_right(map, token, p);
	else
		adjust_left(map, token, p);
}

void	adjust_right(t_map *map, t_token *token, t_coords *p)
{
	int			i;
	t_coords	tmp;
	long double	d_o;
	long double	d_c;

	i = 0;
	while (i < token->cnt_tiles)
	{
		tmp.x = p->x + token->tiles[i].x;
		tmp.y = p->y + token->tiles[i].y;
		d_o = dist_direct(map, &(map->right.edge));
		d_c = dist_direct(map, &tmp);
		if (d_c > d_o)
			map->right.edge = tmp;
		i++;
	}
	map->right.cr = angle_ratio(&(map->right.crit), &(map->right.edge), 'l');
}

void	adjust_left(t_map *map, t_token *token, t_coords *p)
{
	int			i;
	t_coords	tmp;
	long double	d_o;
	long double	d_c;

	i = 0;
	while (i < token->cnt_tiles)
	{
		tmp.x = p->x + token->tiles[i].x;
		tmp.y = p->y + token->tiles[i].y;
		d_o = dist_direct(map, &(map->left.edge));
		d_c = dist_direct(map, &tmp);
		if (d_c > d_o)
			map->left.edge = tmp;
		i++;
	}
	map->left.cr = angle_ratio(&(map->left.crit), &(map->left.edge), 'r');
}

void	adjust_left_crit(t_map *map)
{
	t_coords	d;
	t_coords	i;

	d.x = map->main_v.direction.x > 0 ? -1 : 1;
	d.y = map->main_v.direction.y > 0 ? -1 : 1;
	i.x = map->left.edge.x;
	i.y = map->left.edge.y;
	if ((d.x > 0 && d.y > 0) || (d.x < 0 && d.y < 0))
	{
		while (0 < i.x && i.x < map->columns)
		{
			i.x += d.x;
			if (IS_ENEMY(map->map[i.y][i.x]))
			{
				d.x *= -1;
				d.y *= -1;
				l_search_area(map, &i, &d, 'l');
				return ;
			}
		}
	}
	else
	{
		while (0 < i.y && i.y < map->lines)
		{
			i.y += d.y;
			if (IS_ENEMY(map->map[i.y][i.x]))
			{
				d.x *= -1;
				d.y *= -1;
				l_search_area(map, &i, &d, 'l');
				return ;
			}
		}
	}
	i.x = map->left.edge.x;
	i.y = map->left.edge.y;
	l_search_area(map, &i, &d, 'r');
}

void	l_search_area(t_map *map, t_coords *start, t_coords *d, char side)
{
	t_coords	i;
	int			change;

	ft_log("l_search start[%d, %d] | d[%d, %d] | side = '%c'\n", start->y, start->x, d->y, d->x, side);
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
				ft_log("tile[%d, %d] | Current = %0.3f | i_rat = %0.3f\n",i.y,i.x, map->left.cr, angle_ratio(&(map->left.edge), &i, side));
				if (map->left.cr > angle_ratio(&(map->left.edge), &i, side == 'w' ? 'r' : side) || map->left.cr == 0 || side == 'w')
				{
					map->left.crit = i;
					map->left.cr = angle_ratio(&(map->left.edge), &i, side == 'w' ? 'r' : side);
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
		map->left.crit.x = i.x < 0 ? i.x + 1 : i.x - 1;
		map->left.crit.y = i.y < 0 ? i.y + 1 : i.y - 1;
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
		while (0 < i.x && i.x < map->columns)
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
		while (0 < i.y && i.y < map->lines)
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

	ft_log("r_search start[%d, %d] | d[%d, %d] | side = '%c'\n", start->y, start->x, d->y, d->x, side);
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
				ft_log("tile[%d, %d] | Current = %0.3f | i_rat = %0.3f\n",i.y,i.x, map->right.cr, angle_ratio(&(map->right.edge), &i, side));
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