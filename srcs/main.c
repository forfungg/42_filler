/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:36:03 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/09 14:55:39 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		main(int ac, char **av)
{
	t_game	*game;
	char	*str;

	game = (t_game *)malloc(sizeof(t_game));
	ft_log("\n************START***********\n");
	ft_bzero(game, sizeof(t_game));
	game->board.mlx_p = mlx_init();
	game->board.win = mlx_new_window(game->board.mlx_p, 1200, 1000, "Filler Match - Drawn by jnovotny");
	fetch_player(&(game->map));
	ft_log("Player symbol: %c\n", game->map.player);
	ft_log("-------------------------------\n");
	if (ac == 2)
	{
		game->map.fd = open(av[1], O_RDONLY);
		if (game->map.fd == -1)
			filler_error("Failed to open the map file");
		get_next_line(game->map.fd, &str);
		fetch_mapsize(&(game->map), str);
		ft_log("Map dimensions: %d %d\n", game->map.lines, game->map.columns);
		fetch_map(&(game->map));
		free(str);
		close(game->map.fd);
	}
	mlx_hook(game->board.win, 2, 0, key_press, game);
	mlx_loop_hook(game->board.mlx_p, feed_data, game);
	// feed_data(&map, &token, board);
	mlx_loop(game->board.mlx_p);
	return(0);
}
/* TO-DO 
	
	- introduce the critical points! (guarantee win)
	- visual key interactions (esc, vectors?, reset (after drawing some shit))
	- legend
	- strat log?

	- norm and clean up
	
	- fix graphics (right line is 2p)
*/