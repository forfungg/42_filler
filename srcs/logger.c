/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 17:20:01 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/10 19:04:40 by jnovotny         ###   ########.fr       */
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
	ft_log(">>left branch:\tedge[%d, %d]\n\t\t\t\tcrit[%d, %d]\n\t\t\t\tcr = %.3f\n", map->left.edge.y, map->left.edge.x, map->left.crit.y, map->left.crit.x, map->left.cr);
	ft_log(">>right branch:\tedge[%d, %d]\n\t\t\t\tcrit[%d, %d]\n\t\t\t\tcr = %.3f\n", map->right.edge.y, map->right.edge.x, map->right.crit.y, map->right.crit.x, map->right.cr);
	ft_log("Token[%d, %d] | tiles_cnt = %d\n", token->lines, token->columns, token->cnt_tiles);
}
