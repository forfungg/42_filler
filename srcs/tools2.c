/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 20:29:10 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/11 18:24:19 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		abs_val(int a)
{
	return (a < 0 ? -1 * a : a);
}

void	reset_branch(t_map *map, char branch)
{
	if (branch == 'r')
		map->right.edge = ft_near_corner(map, &(map->right.edge));
	else
		map->left.edge = ft_near_corner(map, &(map->left.edge));
}

void	select_best(t_token *token, t_coords *here)
{
	int best;

	if (token->best_left_dist > token->best_right_dist)
		best = token->best_left_dist;
	else
		best = token->best_right_dist;
	if (token->best_edge_dist > best)
		best = token->best_edge_dist;
	if (best == token->best_left_dist)
		token->best = token->best_left;
	else if (best == token->best_right_dist)
		token->best = token->best_right;
	else
		token->best = token->best_edge;
	*here = token->best;
}
