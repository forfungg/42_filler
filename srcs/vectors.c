/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 09:31:19 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/10 15:18:48 by jnovotny         ###   ########.fr       */
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
}

t_coords	get_direction(t_coords *start, t_coords *point)
{
	t_coords direction;

	direction.x = start->x - point->x;
	direction.y = start->y - point->y;
	return (direction);
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
			if (token->tiles[j].x - token->tiles[i].x > token->h_delta)
				token->h_delta = token->tiles[j].x - token->tiles[i].x;
			if (token->tiles[j].y - token->tiles[i].y > token->v_delta)
				token->v_delta = token->tiles[j].y - token->tiles[i].y;
			j++;
		}
		i++;
	}
}

int			is_zero_v(t_vector *v)
{
	if (v->start.x == 0 && v->start.y == 0 &&\
		v->direction.x == 0 && v->direction.y == 0)
		return (1);
	return (0);
}
