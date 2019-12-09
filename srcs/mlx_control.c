/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 11:11:07 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/09 12:11:51 by jnovotny         ###   ########.fr       */
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
	else if (key == 5)
		game_over_show(&(game->board));
	return (0);
}