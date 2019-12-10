/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scoring.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:30:33 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/10 21:21:03 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		tile_score(t_map *map, t_coords *t, char side)
{
	int	res;
	int nb_f;
	int nb_e;
	int mp;

	nb_f = 0;
	nb_e = 0;
	res = 0;
	if (t->x > 0 && map->map[t->y][t->x - 1] != '.')
		map->map[t->y][t->x - 1] == map->player ? nb_f++ : nb_e++;
	if (t->y > 0 && map->map[t->y - 1][t->x] != '.')
		map->map[t->y - 1][t->x] == map->player ? nb_f++ : nb_e++;
	if (t->x < map->columns - 1 && map->map[t->y][t->x + 1] != '.')
		map->map[t->y][t->x + 1] == map->player ? nb_f++ : nb_e++;
	if (t->y < map->lines - 1 && map->map[t->y + 1][t->x] != '.')
		map->map[t->y + 1][t->x] == map->player ? nb_f++ : nb_e++;
	mp = t->x == 0 || t->y == 0 ? 2500 : 1000;
	mp = t->x == map->columns - 1 || t->y == map->lines - 1 ? 2500 : 1000;
	res += nb_e * nb_e * nb_e * mp;
	return (res + distance_score(map, t, side));
}

int		distance_score(t_map *map, t_coords *t, char side)
{
	int			res;

	res = 0;
	if (side == 'r')
		res = map-> columns < 50 ? (int)(dist_right(map, t) * 10 * angle_ratio(&(map->right.edge), t, 'r')) : (int)(dist_right(map, t) * 10);
	else if (side == 'l')
		res = map-> columns < 50 ? (int)(dist_left(map, t) * 10 * angle_ratio(&(map->left.edge), t, 'l')) : (int)(dist_left(map, t) * 10);
	// res += (int)(dist_direct(map, t) * 10);
	return (res);
}

int		move_score(t_map *map, t_token *token, t_coords *here, char side)
{
	int			i;
	int			res;
	int			ts;
	t_coords	tmp;

	i = 0;
	res = 0;
	while (i < token->cnt_tiles)
	{
		tmp.x = here->x + token->tiles[i].x;
		tmp.y = here->y + token->tiles[i].y;
		ts = tile_score(map, &tmp, side);
		res += ts;
		i++;
	}
	return (res);
}
