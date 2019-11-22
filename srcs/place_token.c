/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 10:22:41 by jnovotny          #+#    #+#             */
/*   Updated: 2019/11/22 14:21:26 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	place_token(t_map *map, t_token *token)
{
	
	ft_printf("19 28");
	ft_bzero((void*)token, sizeof(t_token));
	ft_bzero((void*)map, sizeof(t_map));
	map->map = NULL;
	token->map = NULL;
}