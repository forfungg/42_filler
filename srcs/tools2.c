/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 20:29:10 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/11 14:19:06 by jnovotny         ###   ########.fr       */
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
