/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 11:11:07 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/09 17:49:33 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		key_press(int key, t_game *game)
{
	if (key == 53)
	{
		ft_bzero(game, sizeof(t_game));
		exit(0);
	}
	return (0);
}
