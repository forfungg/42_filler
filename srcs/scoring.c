/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scoring.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:30:33 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/02 17:51:17 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		tile_score(t_map *map, t_coords *t)
{
	int	res;
	int nb_f;
	int nb_e;

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
	


	// res += nb_f;
	res += nb_e * nb_e * nb_e * 100;
	ft_log("enemy_neigh = %d | ", res);
	return (res + distance_score(map, t));
}

int		distance_score(t_map *map, t_coords *t)
{
	// int			d1;
	// t_coords	tmp;
	int			res;

	res = (int)(dist_direct(map, t) * 100);

	// res = 0;
	// tmp.x = 0;
	// tmp.y = 0;
	// d1 = 2 * ft_m_dist(&tmp, start) - ft_m_dist(&tmp, t); // left top
	// (t->x >=  map->columns / 2) && (t->y >= map->lines / 2) ? res += d1 : 0;
	// tmp.x = map->columns - 1;
	// d1 = 2 * ft_m_dist(&tmp, start) - ft_m_dist(&tmp, t); // right top
	// (t->x <=  map->columns / 2) && (t->y >= map->lines / 2) ? res += d1 : 0;
	// tmp.y = map->lines - 1;
	// d1 = 2 * ft_m_dist(&tmp, start) - ft_m_dist(&tmp, t); // right bottom
	// (t->x <=  map->columns / 2) && (t->y <= map->lines / 2) ? res += d1 : 0;
	// tmp.x = 0;
	// d1 = 2 * ft_m_dist(&tmp, start) - ft_m_dist(&tmp, t); //left bottom
	// (t->x >=  map->columns / 2) && (t->y <= map->lines / 2) ? res += d1 : 0;

	ft_log("dist_res = %d | ", res);
	return (res);
}

int		move_score(t_map *map, t_token *token, t_coords *here)
{
	int i;
	int res;
	int ts;
	t_coords tmp;

	i = 0;
	res = 0;
	while (i < token->cnt_tiles)
	{
		tmp.x = here->x + token->tiles[i].x;
		tmp.y = here->y + token->tiles[i].y;
		ft_log("Tile[%d][%d]:\t", tmp.y, tmp.x);
		ts = tile_score(map, &tmp);
		ft_log("| %d\n", ts);
		res += ts;
		i++;
	}
	ft_log("m_score = %d\n", res);
	return(res);
}

// void	adjust_crit_p(t_map *map, t_token *token, t_coords *p)
// {
// 	int	i;
// 	int	j;
// 	i = 0;
// 	while (i < map->lines)
// 	{
// 		j = 0;
// 		while (j < map->columns)
// 		{

// 		}
// 	}

// }

void	adjust_edge(t_map *map, t_token *token, t_coords *p)
{
	int i;
	t_coords tmp;
	long double d_o;
	long double d_c;

	i = 0;
	anchor_token(token, 0);
	// ft_log("-> dist l_edge %.3Lf | dist r_edge %.3Lf\n", ft_m_dist(&(map->left.edge), p), ft_m_dist(&(map->right.edge), p));
	if (ft_m_dist(&(map->left.edge), p) > ft_m_dist(&(map->right.edge), p))
	{
		while (i < token->cnt_tiles)
		{
			tmp.x = p->x + token->tiles[i].x;
			tmp.y = p->y + token->tiles[i].y;
			// ft_log("->R: p[%d; %d] | t(%d)[%d; %d]\n", p->y, p->x, i, token->tiles[i].y, token->tiles[i].x);
			// ft_log("->R: tmp[%d; %d]\n", tmp.y, tmp.x);
			// ft_log("->R: r_e[%d; %d] | m_s[%d; %d]\n", map->right.edge.y, map->right.edge.x, map->main_v.start.y, map->main_v.start.x);
			d_o = dist_direct(map, &(map->right.edge));
			d_c = dist_direct(map, &tmp);
			// ft_log("->R: c_dist: %.3Lf | o_dist: %.3Lf\n", d_c, d_o);
			if ( d_c > d_o)
				map->right.edge = tmp;
			i++;
		}
	}
	else
	{
		while (i < token->cnt_tiles)
		{
			tmp.x = p->x + token->tiles[i].x;
			tmp.y = p->y + token->tiles[i].y;
			// ft_log("->L: p[%d; %d] | t(%d)[%d; %d]\n", p->y, p->x, i, token->tiles[i].y, token->tiles[i].x);
			// ft_log("->L: tmp[%d; %d]\n", tmp.y, tmp.x);
			// ft_log("->L: l_e[%d; %d] | m_s[%d; %d]\n", map->left.edge.y, map->left.edge.x, map->main_v.start.y, map->main_v.start.x);
			d_o = dist_direct(map, &(map->left.edge));
			d_c = dist_direct(map, &tmp);
			// ft_log("->L: c_dist: %.3Lf | o_dist: %.3Lf\n", d_c, d_o);
			if ( d_c > d_o)
				map->left.edge = tmp;
			i++;
		}
	}
}

// void	map_score(t_map *map, t_scoretab *tab)
// {
// 	int i;
// 	int j;

// 	i = tab->anchor.y;
// 	while (i < tab->anchor.y + tab->lines)
// 	{
// 		j = tab->anchor.x;
// 		while (j < tab->anchor.x + tab->columns)
// 		{
// 			if(IS_FREE(j, i))
// 				tab->score += tile_score(map, tab);
// 		}
// 	}
// }