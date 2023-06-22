/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_hooks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:25:18 by mprofett          #+#    #+#             */
/*   Updated: 2023/02/10 09:00:28 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	end_of_game(t_display *display, char *end_msg)
{
	{
		if (end_msg)
			ft_printf("%s\n", end_msg);
		free_display(display);
		exit(EXIT_SUCCESS);
	}
}

void	update_tiles(t_display *display, t_tile_datas *next_pos)
{
	if (next_pos->type == 'C')
		--display->map->nbr_collectibles;
	if (display->map->nbr_collectibles == 0 && next_pos->type == 'E')
		end_of_game(display, "You win");
	display->map->player->type = '0';
	next_pos->type = 'P';
	display->map->player = next_pos;
	ft_printf("%d\n", ++display->nbr_moves);
}

int	ft_key_hook(int key, t_display *display)
{
	t_tile_datas	*next_pos;

	next_pos = NULL;
	if (key == 53)
		end_of_game(display, NULL);
	if (key == 13 && display->map->player->y > 1)
		next_pos = display->map->tiles[display->map->player->tile_nbr
			- display->map->width];
	if (key == 2 && display->map->player->x < display->map->width - 2)
		next_pos = display->map->tiles[(display->map->player->tile_nbr + 1)];
	if (key == 0 && display->map->player->x > 1)
		next_pos = display->map->tiles[(display->map->player->tile_nbr - 1)];
	if (key == 1 && display->map->player->y < display->map->height - 2)
		next_pos = display->map->tiles[(display->map->player->tile_nbr
				+ display->map->width)];
	if (next_pos && next_pos->type != '1'
		&& !(next_pos->type == 'E' && display->map->nbr_collectibles > 0))
		update_tiles(display, next_pos);
	if (display->nbr_moves > 1000)
		end_of_game(display, "You died");
	return (0);
}

int	ft_mlx_hook(t_display *display)
{
	free_display(display);
	exit (EXIT_SUCCESS);
	return (0);
}

int	ft_loop_hook(t_display *display)
{
	static int	i = -1;
	void		*img_ptr;

	mlx_clear_window(display->mlx, display->win);
	while (++i < (display->map->height * display->map->width))
	{
		if (display->map->tiles[i]->type == 'C')
			img_ptr = display->map->img_collec;
		else if (display->map->tiles[i]->type == '0')
			img_ptr = display->map->img_empty;
		else if (display->map->tiles[i]->type == 'E')
			img_ptr = display->map->img_exit;
		else if (display->map->tiles[i]->type == 'P')
			img_ptr = display->map->img_player;
		else if (display->map->tiles[i]->type == '1')
			img_ptr = display->map->img_wall;
		mlx_put_image_to_window(display->mlx, display->win, img_ptr,
			display->map->tiles[i]->x * 32, display->map->tiles[i]->y * 32);
	}
	i = -1;
	return (0);
}
