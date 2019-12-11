/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge_strat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 10:10:46 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/11 16:58:41 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void			find_place_edge(t_game *game, t_coords *i)
{
	t_coords l_top;
	t_coords r_bot;

	l_top = left_top(&(game->map), &(game->token), 'e');
	r_bot = right_bottom(&(game->map), &(game->token), 'e');
	while (1)
	{
		i->y = l_top.y;
		while (i->y < r_bot.y)
		{
			i->x = l_top.x;
			while (i->x < r_bot.x)
			{
				if (IS_MINEG(game->map.map[i->y][i->x]))
					check_place(&(game->map), &(game->token), i, 'e');
				i->x++;
			}
			i->y++;
		}
		if (game->token.best_edge.x < 0 || game->token.best_edge.y < 0)
			resize_square(game, &l_top, &r_bot);
		else
			return ;
	}
}

long double		dist_edge(t_map *map, t_coords *p)
{
	long double a;
	long double b;

	a = ft_m_dist(p, &(map->edge.crit));
	b = ft_m_dist(&(map->edge.edge), &(map->edge.crit));
	return (100 * (b - a));
}

void			adjust_edge_strat(t_map *map, t_token *token, t_coords *p)
{
	int			t;
	t_coords	i;
	long double	d_o;
	long double	d_c;

	t = 0;
	if ((map->edge.edge.x > 0 && map->edge.edge.x < map->columns - 1) &&\
		(map->edge.edge.y > 0 && map->edge.edge.y < map->lines - 1))
	{
		while (t < token->cnt_tiles)
		{
			i.x = p->x + token->tiles[t].x;
			i.y = p->y + token->tiles[t].y;
			d_o = ft_m_dist(&(map->edge.edge), &(map->edge.crit));
			d_c = ft_m_dist(&i, &(map->edge.crit));
			if (d_c < d_o)
				map->edge.edge = i;
			t++;
		}
		return ;
	}
	set_captured(map);
	find_new_edge(map);
}

void			find_new_edge(t_map *map)
{
	t_coords	i;

	ft_log("@find_new_edge\n");
	i.y = map->lines / 2 - map->lines / 5;
	while (0 < i.y && i.y < map->lines - 1)
	{
		i.y++;
		i.x = map->columns / 2 - map->columns / 5;
		while (0 < i.x && i.x < map->columns - 1)
		{
			i.x++;
			if (IS_MINE(map->map[i.y][i.x]))
			{
				ft_log("i[%d, %d]\n", i.y, i.x);
				map->edge.edge.x = i.x;
				map->edge.edge.y = i.y;
				set_edge_strat(map);
				return ;
			}
		}
	}
	map->edge.edge.x = map->right.edge.x;
	map->edge.edge.y = map->right.edge.y;
	set_edge_strat(map);
}

void			set_captured(t_map *map)
{
	t_coords p;

	p = map->edge.edge;
	if ((p.x == 0 && p.y <= map->lines / 2) ||\
		(p.y == 0 && p.x <= map->columns / 2))
		map->corner.lt = 1;
	else if ((p.x == 0 && p.y >= map->lines / 2) ||\
		(p.y == map->lines - 1 && p.x <= map->columns / 2))
		map->corner.lb = 1;
	else if ((p.x == map->columns - 1 && p.y <= map->lines / 2) ||\
		(p.y == 0 && p.x >= map->columns / 2))
		map->corner.rt = 1;
	else if ((p.x == map->columns - 1 && p.y >= map->lines / 2) ||\
		(p.y == map->lines - 1 && p.x >= map->columns / 2))
		map->corner.rb = 1;
	ft_log("@set_corners: lt = %d | rt = %d | lb = %d | rb = %d\n", map->corner.lt, map->corner.rt, map->corner.lb, map->corner.rb);
}
