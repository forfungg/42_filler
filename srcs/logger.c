/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 17:20:01 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/09 16:53:26 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	ft_log(char *msg, ...)
{
	va_list	args;
	FILE	*log_file;

	log_file = fopen("jn_log.txt", "a+");
	va_start(args, msg);
	vfprintf(log_file, msg, args);
	fflush(log_file);
	va_end(args);
	fclose(log_file);
}

void	ft_log_status(t_map *map, t_token *token)
{
	ft_log("Pre-Placement Status\n");
	ft_log(">>main_v [%d; %d]->[%d; %d]\n", map->main_v.start.y, map->main_v.start.x, map->main_v.direction.y, map->main_v.direction.x);
	ft_log(">>left branch:\tedge[%d, %d]\n\t\t\t\tcrit_max[%d, %d]\n\t\t\t\tcrit_min[%d, %d]\n", map->left.edge.y, map->left.edge.x, map->left.crit_max.y, map->left.crit_max.x, map->left.crit_min.y, map->left.crit_min.x);
	ft_log(">>right branch:\tedge[%d, %d]\n\t\t\t\tcrit_max[%d, %d]\n\t\t\t\tcrit_min[%d, %d]\n", map->right.edge.y, map->right.edge.x, map->right.crit_max.y, map->right.crit_max.x, map->right.crit_min.y, map->right.crit_min.x);
	ft_log(">>Token h_delta = %d | v_delta = %d\n", token->h_delta, token->v_delta);
}
