/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:37:02 by jnovotny          #+#    #+#             */
/*   Updated: 2019/11/27 19:51:00 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

# define IS_DIGIT(x) (x >= '0' && x <= '9')
# define IS_MINE(x) (x == map->player || x == map->player + 32)
# define IS_ENEMY(x) (x == map->enemy || x == map->enemy + 32)
# define IS_ANCHOR(i) (token->tiles[i].x == 0 && token->tiles[i].y == 0)
# define IS_FREE(x,y) (map->map[y][x] == '.')
# define IS_STAR(x,y) (token->map[y][x] == '*')
# define TX(i) (token->tiles[i].x)
# define TY(i) (token->tiles[i].y)
# define MAP_LOG 1

typedef struct	s_coords
{
	int	x;
	int	y;
}				t_coords;


typedef struct	s_token
{
	int			lines;
	int			columns;
	char		**map;
	int			cnt_tiles;
	t_coords	*tiles;
	t_coords	best;
	int			best_dist;
	
}				t_token;

typedef struct	s_map
{
	int		lines;
	int		columns;
	char	**map;
	char	**move;
	int		my_area;
	int		enemy_area;
	char	player;
	char	enemy;
	int		fd;
}				t_map;


/*
** Fetch Information Functions
*/

void			fetch_player(t_map *map);
void			feed_data(t_map *map, t_token *token);
void			fetch_mapsize(t_map *map, char *str);
void			fetch_map(t_map *map);
void			fetch_tokensize(t_token *token, char *str);
void			fetch_token(t_token *token);
void			transcribe_token(t_token *token);
void			init_tiles(t_token *token);
void			grabmap_file(t_map *map);

/*
** Logic Functions
*/

void			place_token(t_map *map, t_token *token);
void			find_place(t_map *map, t_token *token, t_coords *i);
int				check_place(t_map *map, t_token *token, t_coords *here);
int				is_fit(t_map *map, t_token *token, t_coords *here);
void			ft_middle(t_map *map, t_coords *center);
int				ft_m_dist(const t_coords *a, const t_coords *b);
void			find_mine(t_map *map, t_coords *mine);
void			find_enemy(t_map *map, t_coords *enemy);
int				player_distance(t_map *map);
void			asses_position(t_map *map, t_token *token, t_coords *here);

/*
**	Print Functions
*/

void			print_map(t_map *map);
void			place_token(t_map *map, t_token *token);
void			filler_error(char *str);
void			token_to_map(t_map *map, t_token *token);

/*
** Supportive tools
*/

void			skip_line(int fd);
void			anchor_token(t_token *token, int i);
void			adjust_out(t_token *token);
void			ft_log(char *msg, ...);
void			reset_game(t_map *map, t_token *token);
void			mapcpy(t_map *src);
void			mapdel(t_map *map);
void			movedel(t_map *map);
void			tokendel(t_token *token);
#endif
