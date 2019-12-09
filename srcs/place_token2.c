/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_token2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 10:22:41 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/09 17:55:24 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		player_distance(t_map *map)
{
	t_coords mine;
	t_coords enemy;

	find_enemy(map, &enemy);
	find_mine(map, &mine);
	return (ft_m_dist(&enemy, &mine));
}

void	find_enemy(t_map *map, t_coords *enemy)
{
	t_coords current;
	t_coords center;

	ft_bzero(enemy, sizeof(t_coords));
	ft_middle(map, &center);
	current.y = 0;
	while (current.y < map->lines)
	{
		current.x = 0;
		while (current.x < map->columns)
		{
			if (IS_ENEMY(map->map[current.y][current.x]) &&\
				ft_m_dist(&current, &center) < ft_m_dist(enemy, &center))
			{
				enemy->x = current.x;
				enemy->y = current.y;
			}
			current.x++;
		}
		current.y++;
	}
}

void	find_mine(t_map *map, t_coords *mine)
{
	t_coords current;
	t_coords center;

	ft_bzero(mine, sizeof(t_coords));
	ft_middle(map, &center);
	current.y = 0;
	while (current.y < map->lines)
	{
		current.x = 0;
		while (current.x < map->columns)
		{
			if (IS_MINE(map->map[current.y][current.x]) &&\
				ft_m_dist(&current, &center) < ft_m_dist(mine, &center))
			{
				mine->x = current.x;
				mine->y = current.y;
			}
			current.x++;
		}
		current.y++;
	}
}
