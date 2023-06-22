/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 09:28:10 by mprofett          #+#    #+#             */
/*   Updated: 2023/02/10 09:29:04 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "mlx/mlx.h"

typedef struct s_tile_datas
{
	int		x;
	int		y;
	int		tile_nbr;
	int		is_accessible;
	char	type;
}				t_tile_datas;

typedef struct s_map
{
	int				width;
	int				height;
	int				nbr_player;
	int				nbr_collectibles;
	int				nbr_exit;
	int				nbr_tiles;
	int				player_is_moving;
	t_tile_datas	**tiles;
	t_tile_datas	*player;
	t_tile_datas	*player_next_pos;
	void			*img_collec;
	void			*img_death;
	void			*img_empty;
	void			*img_exit;
	void			*img_player;
	void			*img_wall;
}				t_map;

typedef struct s_display_datas
{
	void	*mlx;
	void	*win;
	t_map	*map;
	void	**player_set;
	void	**moves_set;
	int		map_is_initialized;
	int		textures_and_sprites_initialized;
	int		nbr_moves;
	char	*moves;
}				t_display;

void	init_textures(t_display *display, int x, int y);
void	init_sprites(t_display *display);

int		ft_key_hook(int key, t_display *display);
int		ft_mlx_hook(t_display *display);
int		ft_loop_hook(t_display *display);

int		valid_path_on_map(t_display *display, t_tile_datas *pos);
void	get_map_values(t_display *display, char *map_name);
char	*read_map(t_display *display, char *map_name);

void	free_display(t_display *display);
void	map_error_and_exit(t_display *display, char *error_msg);
void	strerror_and_exit(t_display *display, char *error_msg);

char	*ft_strjoin_without_nl(char const *s1, char const *s2);
char	*get_tiles_values(t_display *display, int fd);
void	update_tiles(t_display *display, t_tile_datas *next_pos);
void	update_player_pos(t_display *display, t_tile_datas *new_p, int key);

#endif
