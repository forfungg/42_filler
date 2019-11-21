/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:37:02 by jnovotny          #+#    #+#             */
/*   Updated: 2019/11/21 17:03:01 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

typedef struct	s_coords
{
	size_t	x;
	size_t	y;
}				t_coords;

typedef struct	s_token
{
	size_t lines;
	size_t columns;
	
}				t_token;

typedef struct	s_map
{
	size_t	lines;
	size_t	columns;
	char	**map;
	size_t	my_area;
	size_t	enemy_area;
	int		player;
}				t_map;


/*
** Fetch Information Functions
*/
void		fetch_player(t_map *map);
/*
** Logic Functions
*/

/*
**	Print Functions
*/

void			filler_error(char *str);
#endif