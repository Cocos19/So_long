/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_images_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 19:54:42 by mprofett          #+#    #+#             */
/*   Updated: 2023/02/09 20:00:53 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	init_textures(t_display *display, int x, int y)
{
	display->map->img_collec
		= mlx_xpm_file_to_image(display->mlx, "textures/C.xpm", &x, &y);
	display->map->img_death
		= mlx_xpm_file_to_image(display->mlx, "textures/D.xpm", &x, &y);
	display->map->img_exit
		= mlx_xpm_file_to_image(display->mlx, "textures/E.xpm", &x, &y);
	display->map->img_player
		= display->player_set[4];
	display->map->img_empty
		= mlx_xpm_file_to_image(display->mlx, "textures/0.xpm", &x, &y);
	display->map->img_wall
		= mlx_xpm_file_to_image(display->mlx, "textures/1.xpm", &x, &y);
}

void	init_player(t_display *display, int x, int y)
{
	display->player_set[0]
		= mlx_xpm_file_to_image(display->mlx, "sprites/M0.xpm", &x, &y);
	display->player_set[1]
		= mlx_xpm_file_to_image(display->mlx, "sprites/M1.xpm", &x, &y);
	display->player_set[2]
		= mlx_xpm_file_to_image(display->mlx, "sprites/M2.xpm", &x, &y);
	display->player_set[3]
		= mlx_xpm_file_to_image(display->mlx, "sprites/M3.xpm", &x, &y);
	display->player_set[4]
		= mlx_xpm_file_to_image(display->mlx, "sprites/M4.xpm", &x, &y);
	display->player_set[5]
		= mlx_xpm_file_to_image(display->mlx, "sprites/M5.xpm", &x, &y);
	display->player_set[6]
		= mlx_xpm_file_to_image(display->mlx, "sprites/M6.xpm", &x, &y);
	display->player_set[7]
		= mlx_xpm_file_to_image(display->mlx, "sprites/M7.xpm", &x, &y);
	display->player_set[8]
		= mlx_xpm_file_to_image(display->mlx, "sprites/M8.xpm", &x, &y);
	display->player_set[9]
		= mlx_xpm_file_to_image(display->mlx, "sprites/M9.xpm", &x, &y);
	display->player_set[10]
		= mlx_xpm_file_to_image(display->mlx, "sprites/M10.xpm", &x, &y);
	display->player_set[11]
		= mlx_xpm_file_to_image(display->mlx, "sprites/M11.xpm", &x, &y);
}

void	init_moves_set(t_display *display, int x, int y)
{
	display->moves_set[0]
		= mlx_xpm_file_to_image(display->mlx, "sprites/0.xpm", &x, &y);
	display->moves_set[1]
		= mlx_xpm_file_to_image(display->mlx, "sprites/1.xpm", &x, &y);
	display->moves_set[2]
		= mlx_xpm_file_to_image(display->mlx, "sprites/2.xpm", &x, &y);
	display->moves_set[3]
		= mlx_xpm_file_to_image(display->mlx, "sprites/3.xpm", &x, &y);
	display->moves_set[4]
		= mlx_xpm_file_to_image(display->mlx, "sprites/4.xpm", &x, &y);
	display->moves_set[5]
		= mlx_xpm_file_to_image(display->mlx, "sprites/5.xpm", &x, &y);
	display->moves_set[6]
		= mlx_xpm_file_to_image(display->mlx, "sprites/6.xpm", &x, &y);
	display->moves_set[7]
		= mlx_xpm_file_to_image(display->mlx, "sprites/7.xpm", &x, &y);
	display->moves_set[8]
		= mlx_xpm_file_to_image(display->mlx, "sprites/8.xpm", &x, &y);
	display->moves_set[9]
		= mlx_xpm_file_to_image(display->mlx, "sprites/9.xpm", &x, &y);
}

void	init_sprites(t_display *display)
{
	display->moves = malloc(sizeof(char) * 5);
	if (!display->moves)
		strerror_and_exit(display, "malloc moves display");
	display->moves[0] = '0';
	display->moves[1] = '0';
	display->moves[2] = '0';
	display->moves[3] = '0';
	display->moves[4] = '\0';
	display->nbr_moves = 0;
	display->moves_set = malloc(sizeof(void *) * 10);
	if (!display->moves_set)
		strerror_and_exit(display, "malloc player image set");
	init_moves_set(display, 32, 32);
	display->player_set = malloc(sizeof(void *) * 12);
	if (!display->player_set)
		strerror_and_exit(display, "malloc player image set");
	init_player(display, 32, 32);
}
