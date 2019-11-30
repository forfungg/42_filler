/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 09:31:19 by jnovotny          #+#    #+#             */
/*   Updated: 2019/11/30 19:37:34 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	main_vector(t_map *map)
{
	t_coords mine;
	t_coords enemy;
	
	ft_log("main_vector: ");
	find_mine(map, &mine);
	ft_log("1 | ");
	map->right.edge = mine;
	map->left.edge = mine;
	ft_log("2 | ");
	find_enemy(map, &enemy);
	ft_log("3 | ");
	map->right.crit_max = enemy;
	map->right.crit_min = enemy;
	map->left.crit_max = enemy;
	map->left.crit_min = enemy;
	map->main_v.start = mine;
	ft_log("4 | ");
	map->main_v.direction = get_direction(&mine, &enemy);
	ft_log("5\n");
}

t_coords	get_direction(t_coords *start, t_coords *point)
{
	t_coords direction;

	direction.x = start->x - point->x;
	direction.y = start->y - point->y;
	return(direction);
}

void		get_deltas(t_token *token)
{
	int i;
	int j;
	
	token->v_delta = 0;
	token->h_delta = 0;
	i = 0;
	while (i < token->cnt_tiles)
	{
		j = i + 1;
		while (j < token->cnt_tiles)
		{
			if (token->tiles[i].x - token->tiles[j].x > token->h_delta)
				token->h_delta = token->tiles[i].x - token->tiles[j].x;
			if (token->tiles[i].y - token->tiles[j].y > token->v_delta)
				token->v_delta = token->tiles[i].y - token->tiles[j].y;
			j++;
		}
		i++;
	}
}