/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_points.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 17:27:08 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/11 18:14:46 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	check_surround(t_map *map)
{
	if (is_surround(map, &(map->edge.edge)))
	{
		if (ft_m_dist(&(map->right.edge), &(map->edge.crit)) >\
			ft_m_dist(&(map->left.edge), &(map->edge.crit)))
			map->edge.edge = map->left.edge;
		else
			map->edge.edge = map->right.edge;
	}
}

int		is_surround(t_map *map, t_coords *tile)
{
	if (tile->y > 0 && map->map[tile->y - 1][tile->x] == '.')
		return (0);
	else if (tile->y < map->lines - 1 && map->map[tile->y + 1][tile->x] == '.')
		return (0);
	else if (tile->x > 0 && map->map[tile->y][tile->x - 1] == '.')
		return (0);
	else if (tile->x < map->columns - 1 &&\
		map->map[tile->y][tile->x + 1] == '.')
		return (0);
	else if (tile->y > 0 && tile->x > 0 &&\
		map->map[tile->y - 1][tile->x - 1] == '.')
		return (0);
	else if (tile->y < map->lines - 1 && tile->x < map->columns - 1 &&\
		map->map[tile->y + 1][tile->x + 1] == '.')
		return (0);
	else if (tile->x > 0 && tile->y < map->lines - 1 &&\
		map->map[tile->y + 1][tile->x - 1] == '.')
		return (0);
	else if (tile->x < map->columns - 1 && tile->y > 0 &&\
		map->map[tile->y - 1][tile->x + 1] == '.')
		return (0);
	return (1);
}
