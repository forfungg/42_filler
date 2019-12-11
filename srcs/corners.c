/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corners.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 14:16:09 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/11 17:13:05 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_coords	ft_near_corner(t_map *map, t_coords *p)
{
	long double	best_d;
	t_coords	best;
	t_coords	tmp;
	long double	tmp_d;

	tmp.x = 0;
	tmp.y = 0;
	best_d = ft_m_dist(p, &tmp);
	best = tmp;
	tmp.x = map->columns - 1;
	tmp_d = ft_m_dist(p, &tmp);
	if (tmp_d < best_d)
	{
		best = tmp;
		best_d = tmp_d;
	}
	tmp.y = map->lines - 1;
	tmp_d = ft_m_dist(p, &tmp);
	if (tmp_d < best_d)
	{
		best = tmp;
		best_d = tmp_d;
	}
	tmp.x = 0;
	tmp_d = ft_m_dist(p, &tmp);
	if (tmp_d < best_d)
	{
		best = tmp;
		best_d = tmp_d;
	}
	return (best);
}

t_coords	ft_near_corner_0(t_map *map, t_coords *p)
{
	long double	best_d;
	t_coords	best;
	t_coords	tmp;
	long double	tmp_d;

	tmp.x = 0;
	tmp.y = 0;
	best.x = -1;
	best.y = -1;
	best_d = (long double)10000;
	tmp_d = ft_m_dist(p, &tmp);
	ft_log("Corner distance from [%d, %d]: lt = %.3Lf | ", p->y, p->x, tmp_d);
	if ((tmp_d < best_d) && (map->corner.lt == 0))
	{
		best.x = tmp.x;
		best.y = tmp.y;
		best_d = tmp_d;
	}
	tmp.x = map->columns - 1;
	tmp_d = ft_m_dist(p, &tmp);
	ft_log("rt = %.3Lf | ", tmp_d);
	if (tmp_d < best_d && map->corner.rt == 0)
	{
		best.x = tmp.x;
		best.y = tmp.y;
		best_d = tmp_d;
	}
	tmp.y = map->lines - 1;
	tmp_d = ft_m_dist(p, &tmp);
	ft_log("rb = %.3Lf | ", tmp_d);
	if (tmp_d < best_d && map->corner.rb == 0)
	{
		best.x = tmp.x;
		best.y = tmp.y;
		best_d = tmp_d;
	}
	tmp.x = 0;
	tmp_d = ft_m_dist(p, &tmp);
	ft_log("lb = %.3Lf | ", tmp_d);
	if (tmp_d < best_d && map->corner.lb == 0)
	{
		best.x = tmp.x;
		best.y = tmp.y;
		best_d = tmp_d;
	}
	ft_log("best[%d, %d]\n", best.y, best.x);
	return (best);
}
