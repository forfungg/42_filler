/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strat_adjust.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 18:14:41 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/11 18:41:25 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	adjust_edge(t_map *map, t_token *token, t_coords *p)
{
	anchor_token(token, 0);
	if (token->best_right_dist < token->best_left_dist)
		adjust_left(map, token, p);
	else
		adjust_right(map, token, p);
	adjust_edge_strat(map, token, p);
	check_surround(map);
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
		d_o = dist_right(map, &(map->right.edge)) *\
			angle_ratio(&(map->right.edge), &(map->right.crit), 'r');
		d_c = dist_right(map, &tmp) *\
			angle_ratio(&tmp, &(map->right.crit), 'r');
		if (d_c > d_o)
			map->right.edge = tmp;
		i++;
	}
	if (ft_m_dist(&(map->right.edge), &(map->right.crit)) < 1.1)
		reset_branch(map, 'r');
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
		d_o = dist_left(map, &(map->left.edge)) *\
			angle_ratio(&(map->left.edge), &(map->left.crit), 'l');
		d_c = dist_left(map, &tmp) * angle_ratio(&tmp, &(map->left.crit), 'l');
		if (d_c > d_o)
			map->left.edge = tmp;
		i++;
	}
	if (ft_m_dist(&(map->left.edge), &(map->left.crit)) < 1.1)
		reset_branch(map, 'l');
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
		if (adj_lc_1(map, &i, &d))
			return ;
	}
	else
	{
		if (adj_lc_2(map, &i, &d))
			return ;
	}
	i.x = map->left.edge.x;
	i.y = map->left.edge.y;
	l_search_area(map, &i, &d, 'r');
}
