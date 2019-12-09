/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strat_adjust.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 18:14:41 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/09 18:14:50 by jnovotny         ###   ########.fr       */
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
}
