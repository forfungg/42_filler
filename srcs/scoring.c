/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scoring.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:30:33 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/09 19:58:35 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		tile_score(t_map *map, t_coords *t)
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
	mp = t->x == 0 || t->y == 0 ? 250 : 100;
	mp = t->x == map->columns - 1 || t->y == map->lines - 1 ? 500 : 250;
	res += nb_e * nb_e * nb_e * mp;
	return (res + distance_score(map, t));
}

int		distance_score(t_map *map, t_coords *t)
{
	int			res;

	res = (int)(dist_direct(map, t) * 100);
	return (res);
}

int		move_score(t_map *map, t_token *token, t_coords *here)
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
		ts = tile_score(map, &tmp);
		res += ts;
		i++;
	}
	return (res);
}
