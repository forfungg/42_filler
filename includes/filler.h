/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:37:02 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/11 19:57:30 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "mlx.h"

# define IS_DIGIT(x) (x >= '0' && x <= '9')
# define IS_MINE(x) (x == map->player || x == map->player + 32)
# define IS_MINEG(x) (x == game->map.player || x == game->map.player + 32)
# define IS_ENEMY(x) (x == map->enemy || x == map->enemy + 32)
# define IS_ANCHOR(i) (token->tiles[i].x == 0 && token->tiles[i].y == 0)
# define IS_FREE(x,y) (map->map[y][x] == '.')
# define IS_STAR(x,y) (token->map[y][x] == '*')
# define TX(i) (token->tiles[i].x)
# define TY(i) (token->tiles[i].y)
# define IS_ZERO_P(a) (a->x == 0 && a->y == 0)
# define MAP_LOG 1
# define MLX_RED 16711680
# define MLX_ORANGE 16733440
# define MLX_WHITE 16777215
# define MLX_BLUE 255
# define MLX_GREEN 65280
# define MLX_L_GREEN 11992832
# define MLX_YELLOW 16776960
# define MLX_PINK 16711935
# define MLX_P board->mlx_p
# define MLX_W board->win
# define GG_IMG board->game_over.img
# define G_B_LINES game->board.lines
# define G_B_COLUMNS game->board.columns
# define G_M_LINES game->map.lines
# define G_M_COLUMNS game->map.columns
# define G_T_LINES game->token.lines
# define G_T_COLUMNS game->token.columns
# define GTBR_X game->token.best_right.x
# define GTBR_Y game->token.best_right.y
# define GTBL_X game->token.best_left.x
# define GTBL_Y game->token.best_left.y

typedef struct	s_coords
{
	int	x;
	int	y;
}				t_coords;

typedef struct	s_vector
{
	t_coords	start;
	t_coords	direction;
}				t_vector;

typedef struct	s_strat_branch
{
	t_coords	edge;
	t_coords	crit;
	double		cr;
	t_coords	i;
}				t_branch;

typedef struct	s_corners
{
	int			lt;
	int			rt;
	int			lb;
	int			rb;
}				t_corners;

typedef struct	s_board_img
{
	int		width;
	int		height;
	int		color;
	void	*img;
	char	*img_p;
	int		bpp;
	int		line_s;
	int		endian;
}				t_bimg;

typedef	struct	s_board
{
	void	*mlx_p;
	void	*win;
	int		lines;
	int		columns;
	t_bimg	header;
	t_bimg	bg;
	t_bimg	game_board;
	int		brdoff_l;
	int		brdoff_t;
	t_bimg	empty;
	t_bimg	p1_old;
	t_bimg	p1_new;
	t_bimg	p2_old;
	t_bimg	p2_new;
	t_bimg	game_over;
	t_bimg	cover_score;
}				t_brd;

typedef struct	s_token
{
	int			lines;
	int			columns;
	char		**map;
	int			cnt_tiles;
	t_coords	*tiles;
	t_coords	best_left;
	t_coords	best_right;
	t_coords	best_edge;
	int			best_left_dist;
	int			best_right_dist;
	int			best_edge_dist;
	t_coords	best;
}				t_token;

typedef struct	s_map
{
	int			lines;
	int			columns;
	char		**map;
	t_brd		board;
	char		player;
	int			my_score;
	char		enemy;
	int			en_score;
	t_vector	main_v;
	t_branch	right;
	t_branch	left;
	t_branch	edge;
	t_corners	corner;
}				t_map;

typedef struct	s_game
{
	t_map	map;
	t_token token;
	t_brd	board;
}				t_game;

/*
** Fetch Information Functions
*/

void			fetch_player(t_map *map);
int				feed_data(t_game *game);
void			fetch_mapsize(t_map *map, char *str);
void			fetch_map(t_map *map);
void			fetch_tokensize(t_token *token, char *str);
void			fetch_token(t_token *token);
void			transcribe_token(t_token *token);
void			init_tiles(t_token *token);

/*
** Logic Functions
*/

void			place_token(t_game *game);
void			find_place(t_game *game, t_coords *i, char side);
int				check_place(t_map *map, t_token *token, t_coords *here,\
					char side);
int				is_fit(t_map *map, t_token *token, t_coords *here);
void			ft_middle(t_map *map, t_coords *center);
void			find_mine(t_map *map, t_coords *mine);
void			find_enemy(t_map *map, t_coords *enemy);
int				player_distance(t_map *map);
void			asses_position(t_map *map, t_token *token, t_coords *here,\
					char side);

/*
**	Vectors
*/

t_coords		get_direction(t_coords *start, t_coords *point);
void			main_vector(t_map *map);
int				is_zero_v(t_vector *v);

/*
** Parsing functions
*/

t_coords		left_top(t_map *map, t_token *token, char side);
t_coords		right_bottom(t_map *map, t_token *token, char side);
void			resize_square(t_game *game, t_coords *l_top, t_coords *r_bot);

/*
** Scoring & Strategy Functions
*/

int				move_score(t_map *map, t_token *token, t_coords *here,\
					char side);
int				tile_score(t_map *map, t_coords *t, char side);
int				distance_score(t_map *map, t_coords *t, char side);
void			adjust_edge(t_map *map, t_token *token, t_coords *p);
void			adjust_right(t_map *map, t_token *token, t_coords *p);
void			adjust_left(t_map *map, t_token *token, t_coords *p);
void			adjust_left_crit(t_map *map);
void			adjust_right_crit(t_map *map);
void			l_search_area(t_map *map, t_coords *start, t_coords *d,\
					char side);
int				l_search_area2(t_map *map, t_coords *start, t_coords *d,\
					char s);
void			r_search_area(t_map *map, t_coords *start, t_coords *d,\
					char side);
int				r_search_area2(t_map *map, t_coords *start, t_coords *d,\
					char s);
double			angle_ratio(t_coords *a, t_coords *b, char side);
void			find_place_edge(t_game *game, t_coords *i);
long double		dist_edge(t_map *map, t_coords *p);
void			set_edge_strat(t_map *map);
void			adjust_edge_strat(t_map *map, t_token *token, t_coords *p);
void			find_new_edge(t_map *map);
void			reset_branch(t_map *map, char branch);
void			set_captured(t_map *map);
void			check_surround(t_map *map);
int				is_surround(t_map *map, t_coords *tile);
void			select_best(t_token *token, t_coords *here);
int				adj_lc_1(t_map *map, t_coords *i, t_coords *d);
int				adj_lc_2(t_map *map, t_coords *i, t_coords *d);
int				adj_rc_1(t_map *map, t_coords *i, t_coords *d);
int				adj_rc_2(t_map *map, t_coords *i, t_coords *d);

/*
**	Print Functions
*/

void			print_map(t_map *map);
void			filler_error(char *str);
void			token_to_map(t_map *map, t_token *token);

/*
** Calculus
*/

long double		dist_direct(t_map *map, t_coords *p);
long double		dist_left(t_map *map, t_coords *p);
long double		dist_right(t_map *map, t_coords *p);
long double		ft_sqrt_prec(long double nb, int prec);
long double		ft_m_dist(const t_coords *a, const t_coords *b);
t_coords		ft_near_corner(t_map *map, t_coords *p);
t_coords		ft_near_corner2(t_map *map, t_coords *p, t_coords *best);
t_coords		ft_near_corner_0(t_map *map, t_coords *p);
t_coords		ft_near_corner_02(t_map *map, t_coords *p, t_coords *best);

/*
** Visual
*/

void			map_to_visual(t_map *map, t_brd *board);
void			put_tile(t_brd *board, char c, t_coords *place);
void			enemy_turn(t_map *map, t_brd *board, int t);
void			init_board(t_map *map, t_brd *board);
void			init_header(t_brd *board);
void			init_bg(t_brd *board);
void			init_players(t_brd *board);
void			p_tile_size(t_brd *board, int size);
void			init_game_board(t_brd *board);
void			init_gameover(t_brd *board);
void			init_coverscore(t_brd *board);
void			square_img(void *mlx_ptr, t_bimg *elem);
char			*brd_s_str(int width, int height);
void			game_over_show(t_brd *board);
void			show_score(t_game *game);

/*
** GG
*/

void			place_g(t_brd *board, t_coords *start);
void			place_a(t_brd *board, t_coords *start);
void			place_m(t_brd *board, t_coords *start);
void			place_e(t_brd *board, t_coords *start);
void			place_o(t_brd *board, t_coords *start);
void			place_v(t_brd *board, t_coords *start);
void			place_r(t_brd *board, t_coords *start);
void			place_excl(t_brd *board, t_coords *start);

/*
** MLX control
*/

int				key_press(int key, t_game *game);
void			filler_over(t_game *game);

/*
** Supportive tools
*/

void			skip_line(int fd);
void			anchor_token(t_token *token, int i);
void			adjust_out(t_token *token);
void			ft_log(char *msg, ...);
void			ft_log_status(t_map *map, t_token *token);
void			reset_game(t_map *map, t_token *token);
void			mapdel(t_map *map);
void			tokendel(t_token *token);
void			get_deltas(t_token *token);
int				abs_val(int a);
void			token_best_reset(t_token *token);

#endif
