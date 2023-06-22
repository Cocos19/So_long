/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_free_and_exit_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 20:05:26 by mprofett          #+#    #+#             */
/*   Updated: 2023/02/10 09:30:03 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	free_img_array(t_display *display, void **img_array, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		if (img_array[i])
			mlx_destroy_image(display->mlx, img_array[i]);
}

void	free_map(t_display *display)
{
	int	i;

	i = -1;
	if (display->map->tiles)
	{
		while (++i < display->map->nbr_tiles)
			if (display->map->tiles[i])
				free(display->map->tiles[i]);
	}
	if (display->textures_and_sprites_initialized == 1)
	{
		mlx_destroy_image(display->mlx, display->map->img_collec);
		mlx_destroy_image(display->mlx, display->map->img_death);
		mlx_destroy_image(display->mlx, display->map->img_empty);
		mlx_destroy_image(display->mlx, display->map->img_exit);
		mlx_destroy_image(display->mlx, display->map->img_wall);
	}
	free(display->map);
}

void	free_display(t_display *display)
{
	int	i;

	i = -1;
	if (display->win)
		mlx_destroy_window(display->mlx, display->win);
	if (display->textures_and_sprites_initialized == 1)
		free_img_array(display, display->player_set, 12);
	if (display->textures_and_sprites_initialized == 1)
		free_img_array(display, display->moves_set, 10);
	if (display->moves)
		free(display->moves);
	if (display->map_is_initialized == 1)
		free_map(display);
	if (display->mlx)
		free(display->mlx);
	free(display);
}

void	map_error_and_exit(t_display *display, char *error_msg)
{
	free_display(display);
	ft_printf("Error\n%s\n", error_msg);
	exit (EXIT_FAILURE);
}

void	strerror_and_exit(t_display *display, char *error_msg)
{
	if (display)
		free_display(display);
	ft_printf("Error when %s: %s\n", error_msg, strerror(errno));
	exit (EXIT_FAILURE);
}
