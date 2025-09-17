/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:21:56 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/17 16:57:32 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "types.h"
# include "s_vector.h"

# define DOT_CUB	".cub"
# define DOT_CUBNS	".cubns"

# define W_WIDTH	1200
# define W_HEIGHT	800

# define MMAP_WIDHT		300
# define MMAP_HEIGHT	200

# define NB_TEXTURE		4

# define KEY_CEILING	"C"
# define KEY_FLOOR		"F"
# define KEY_NORTH		"NO"
# define KEY_EAST		"EA"
# define KEY_SOUTH		"SO"
# define KEY_WEST		"WE"

# define KEY_MM_PLAYER	"MM_PLR"
# define KEY_MM_VIEW	"MM_VIEW"
# define KEY_MM_WALL	"MM_1"
# define KEY_MM_EMPTY	"MM_0"
# define KEY_MM_D_OPEN	"MM_DO"
# define KEY_MM_D_CLOSE	"MM_DC"

# define KEY_DOOR		"DR"

# define PLAYER_CHARS	"NSWE"
# define MAP_CHARS		"01 NSWE"
# define MAP_CHARS_BNS	"D"
# define CHAR_DOOR		'D'
# define WALL_CHAR		'1'
# define MTY_CHAR		' '

struct s_mlx
{
	char		title[BUFF_SIZE];

	void		*mlx_ptr;
	void		*win_ptr;
	void		*win_img;
	void		*win_img_paa;
	void		*img_mmap;
	void		*img_settings;

	t_err		error;
	char		err_context[BUFF_SIZE];
};

struct s_xpm_img
{
	void	*p_img;
	t_clr	*p_data;
	int		width;
	int		height;
};

enum {MINR_MAP, MAXR_MAP
};

struct s_pars
{
	t_read		rd;

	t_xpm_img	no_texture;
	t_xpm_img	ea_texture;
	t_xpm_img	so_texture;
	t_xpm_img	we_texture;

	t_xpm_img	door_texture;

	t_clr		color_ceiling;
	uint8_t		ceiling_defined:1;
	t_clr		color_floor;
	uint8_t		floor_defined:1;

	t_clr		mmap_player;
	t_clr		mmap_wall;
	t_clr		mmap_empty;
	t_clr		mmap_view;
	t_clr		mmap_d_open;
	t_clr		mmap_d_closed;

	uint64_t	player[2];
	float		view_angle;
	float		delta_angle;
	float		fov;

	t_vector	vec_map;
	char		**map;
	uint64_t	dim[2];
	int64_t		range_map[2][2];
	char		**resized_map;

	t_doors		doors;

	t_mlx		pmlx;

	uint8_t		bonus:1;
	t_err		error;
	char		err_context[BUFF_SIZE];
};

void		skip_spaces(char *line[]);
void		skip_key_space(char **line);
int			ft_str_space_cmp(const char *str, const char *pat);
int			is_color(const char *line);
int			is_texture(const char *line);
int			ft_isdigit(const char c);
int			is_map(const char *line);
t_err		is_data_full(t_pars *pars);
t_err		check_doors(t_pars *pars);

t_err		pars_color(t_pars *pars, char *line);
t_err		pars_texture(t_pars *pars, char *line);

t_err		flood_fill(t_pars *pars, char **map, uint64_t dim[2]);
t_err		count_players(t_pars *pars, char **map, uint64_t dim[2]);
t_err		read_map(t_pars *pars, const char allowed_char[]);
t_err		pars_map(t_pars *pars);
t_err		pars_data(t_pars *pars);

void		fill_game(t_pars *pars, t_game *game);
t_err		parsing(t_pars *pars);
t_err		init_cub(t_cub *cub, int ac, char *av[]);

t_err		pars_color_bns(t_pars *pars, char *line);
t_err		pars_texture_bonus(t_pars *pars, char *line);
t_err		pars_data_bonus(t_pars *pars);
t_err		pars_map_bonus(t_pars *pars);

#endif
