/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:36:03 by jnovotny          #+#    #+#             */
/*   Updated: 2019/11/21 18:51:50 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		main()
{
	t_token	token;
	t_map	map;

	ft_bzero((void*)&token, sizeof(t_token));
	ft_bzero((void*)&map, sizeof(t_map));
	fetch_player(&map);
	ft_printf("{CYAN}{INV}I'M PLAYER %d{EOC}\n", map.player);
	return (0);
	feed_data(&map, &token);

/*
	- get player number?
	- fetch the map
		Plateau 15 17:					if "Plateau" 	-> atoi lines && atoi columns
    	01234567890123456								-> if diff from original -> error
		000 ......o.......O..			start to read map on this line
		001 .....ooOOOOOOOOOO				-> chop the number off IS_DIGIT i++
		002 ...OOOOOOOOOOOOOO				-> validation while reading?
		003 ..OOOOOOOOOOOOOOO				-> other calculations
		004 .OOOOOOOOOOOOOOOO
		005 ..OOOOOOOOOOOOOOO
		006 ..OOOOOOOOOOOOOOO
		007 ..OOOOOOOOOOOOOOO
		008 ..OOOOOOOOOOOOOOO
		009 ..OOOOOOXXXXXXXXX
		010 ..OXOOOOXXXXXXXXX
		011 .OOXOOOXXXXXXXXXX
		012 .OOXXXXXXXXXXXXXX
		013 ..OXXXXXXXXXXXXXX
		014 ..OXXXXXXXXXXXXXX

	- fetch the token
		Piece 2 3:						if "Piece"	-> atoi lines && atoi columns
		*..											-> read and validate
		*..

	- evaluate strategy
	- place token
	- print the map */
	return(0);
}