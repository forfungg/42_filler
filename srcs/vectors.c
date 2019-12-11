/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 09:31:19 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/11 10:10:59 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
** If looking for parallel vector through point A then the point B
** on such vector can be found by:
** B.x = A.x - main_v.direction.x;
** B.y = A.y - main_v.direction.y;
*/

void		main_vector(t_map *map)
{
	t_coords mine;
	t_coords enemy;

	find_mine(map, &mine);
	map->right.edge = mine;
	map->left.edge = mine;
	find_enemy(map, &enemy);
	map->right.crit = enemy;
	map->right.cr = angle_ratio(&enemy, &mine, 'r');
	map->left.crit = enemy;
	map->left.cr = angle_ratio(&enemy, &mine, 'r');
	map->main_v.start = mine;
	map->main_v.direction = get_direction(&mine, &enemy);
	map->edge.edge = mine;
	// set_edge_strat(map);
}

t_coords	get_direction(t_coords *start, t_coords *point)
{
	t_coords direction;

	direction.x = start->x - point->x;
	direction.y = start->y - point->y;
	return (direction);
}

int			is_zero_v(t_vector *v)
{
	if (v->start.x == 0 && v->start.y == 0 &&\
		v->direction.x == 0 && v->direction.y == 0)
		return (1);
	return (0);
}

void	set_edge_strat(t_map *map)
{
	t_coords tmp;

	map->edge.crit.x = 0;
	map->edge.crit.y = 0;
	map->edge.cr = (double)ft_m_dist(&(map->edge.edge), &(map->edge.crit));
	tmp.x = map->columns - 1;
	tmp.y = 0;
	if ((double)ft_m_dist(&(map->edge.edge), &tmp) <  map->edge.cr)
		map->edge.crit = tmp;
	tmp.x = map->columns - 1;
	tmp.y = map->lines - 1;
	if ((double)ft_m_dist(&(map->edge.edge), &tmp) <  map->edge.cr)
		map->edge.crit = tmp;
	tmp.x = 0;
	tmp.y = map->lines - 1;
	if ((double)ft_m_dist(&(map->edge.edge), &tmp) <  map->edge.cr)
		map->edge.crit = tmp;
}