/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge_strat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 10:10:46 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/11 12:47:46 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	find_place_edge(t_game *game, t_coords *i)
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

void	adjust_edge_strat(t_map *map, t_token *token, t_coords *p)
{
	int	t;
	t_coords i;
	t_coords d;
	long double d_o;
	long double d_c;
	
	t = 0;
	if (map->edge.edge.x != 0 && map->edge.edge.y != 0 && map->edge.edge.x != map->columns - 1 && map->edge.edge.y != map->lines - 1)
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
	d.x = map->right.edge.x - map->left.crit.y > 0 ? 1 : -1;
	d.y = map->left.edge.y - map->right.crit.x > 0 ? 1 : -1;
	i.y = map->edge.crit.y == 0 ? (map->lines + map->lines / 10) / 2 : (map->lines - map->lines / 10) / 2;
	while (0 < i.y && i.y < map->lines - 1)
	{
		i.y += d.y;
		i.x = map->edge.crit.x == 0 ? (map->columns + map->columns / 10) / 2 : (map->columns - map->columns / 10) / 2;
		while (0 < i.x && i.x < map->columns - 1)
		{
			i.x += d.x;
			if (IS_MINE(map->map[i.y][i.x]))
			{
				map->edge.edge.x = i.x;
				map->edge.edge.y = i.y;
				set_edge_strat(map);
				return ;
			}
		}
	}
}

void	reset_branch(t_map *map, char branch)
{
	if (branch == 'r')
		map->right.edge = ft_near_corner(map, &(map->right.edge));
	else
		map->left.edge = ft_near_corner(map, &(map->left.edge));
}

t_coords	ft_near_corner(t_map *map, t_coords *p)
{
	long double best_d;
	t_coords best;
	t_coords tmp;
	long double tmp_d;

	tmp.x = 0;
	tmp.y = 0;
	best_d = ft_m_dist(p, &tmp);
	best = tmp;
	tmp.x = map->columns - 1;
	tmp_d = ft_m_dist(p, &tmp);
	tmp_d < best_d ? best = tmp : best;
	tmp.y = map->lines - 1;
	tmp_d = ft_m_dist(p, &tmp);
	tmp_d < best_d ? best = tmp : best;
	tmp.x = 0;
	tmp_d = ft_m_dist(p, &tmp);
	tmp_d < best_d ? best = tmp : best;
	return (best);
}

t_coords	ft_near_corner_0(t_map *map, t_coords *p)
{
	long double best_d;
	t_coords best;
	t_coords tmp;
	long double tmp_d;

	tmp.x = 0;
	tmp.y = 0;
	best.x = -1;
	best.y = -1;
	best_d = map->columns * map->columns + map->lines * map->lines;
	tmp_d = ft_m_dist(p, &tmp);
	tmp_d < best_d && !map->corner.lt ? best = tmp : best;
	tmp.x = map->columns - 1;
	tmp_d = ft_m_dist(p, &tmp);
	tmp_d < best_d && !map->corner.rt ? best = tmp : best;
	tmp.y = map->lines - 1;
	tmp_d = ft_m_dist(p, &tmp);
	tmp_d < best_d && !map->corner.rb ? best = tmp : best;
	tmp.x = 0;
	tmp_d = ft_m_dist(p, &tmp);
	tmp_d < best_d && !map->corner.lb ? best = tmp : best;
	return (best);
}

void	set_captured(t_map *map)
{
	t_coords p;

	p = map->edge.edge;
	if ((p.x == 0 && p.y <= map->lines / 2) || (p.y == 0 && p.x <= map->columns / 2))
		map->corner.lt = 1;
	else if ((p.x == 0 && p.y >= map->lines / 2) || (p.y == map->lines - 1 && p.x <= map->columns / 2))
		map->corner.lb = 1;
	else if ((p.x == map->columns - 1 && p.y <= map->lines / 2) || (p.y == 0 && p.x >= map->columns / 2))
		map->corner.rt = 1;
	else if ((p.x == map->columns - 1 && p.y >= map->lines / 2) || (p.y == map->lines - 1 && p.x >= map->columns / 2))
		map->corner.rb = 1;
}