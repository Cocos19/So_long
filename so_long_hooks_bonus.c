/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_hooks_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:09:34 by mprofett          #+#    #+#             */
/*   Updated: 2023/02/10 09:15:34 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	ft_key_hook(int key, t_display *display)
{
	t_tile_datas	*new_p;

	new_p = NULL;
	if (key == 53)
	{
		free_display(display);
		exit(EXIT_SUCCESS);
	}
	if (display->map->player_is_moving == -1)
	{
		if (key == 13 && display->map->player->y > 1)
			new_p = display->map->tiles[display->map->player->tile_nbr
				- display->map->width];
		if (key == 2 && display->map->player->x < display->map->width - 2)
			new_p = display->map->tiles[(display->map->player->tile_nbr + 1)];
		if (key == 0 && display->map->player->x > 1)
			new_p = display->map->tiles[(display->map->player->tile_nbr - 1)];
		if (key == 1 && display->map->player->y < display->map->height - 2)
			new_p = display->map->tiles[(display->map->player->tile_nbr
					+ display->map->width)];
		update_player_pos(display, new_p, key);
	}
	return (0);
}

int	ft_mlx_hook(t_display *display)
{
	free_display(display);
	exit (EXIT_SUCCESS);
	return (0);
}

void	change_player_img(t_display *display, int frames_counter)
{
	static int	img = -1;

	if (frames_counter == 0)
	{
		if (display->map->player_is_moving == 13)
			img = 0;
		else if (display->map->player_is_moving == 2)
			img = 9;
		else if (display->map->player_is_moving == 0)
			img = 6;
		else if (display->map->player_is_moving == 1)
			img = 3;
	}
	else if (frames_counter == 1)
		++img;
	else if (frames_counter == 2)
	{
		++img;
		update_tiles(display, display->map->player_next_pos);
	}
	else
		--img;
	display->map->img_player = display->player_set[img];
}

void	*get_img_to_put(t_display *display, int i)
{
	if (i == display->map->width - 4 && display->nbr_moves > 999)
		return (display->moves_set[display->moves[ft_strlen(display->moves)
					- 4] - 48]);
	else if (i == display->map->width - 3 && display->nbr_moves > 99)
		return (display->moves_set[display->moves[ft_strlen(display->moves)
					- 3] - 48]);
	else if (i == display->map->width - 2 && display->nbr_moves > 9)
		return (display->moves_set[display->moves[ft_strlen(display->moves)
					- 2] - 48]);
	else if (i == display->map->width - 1)
		return (display->moves_set[display->moves[ft_strlen(display->moves)
					- 1] - 48]);
	else if (display->map->tiles[i]->type == 'C')
		return (display->map->img_collec);
	else if (display->map->tiles[i]->type == '0')
		return (display->map->img_empty);
	else if (display->map->tiles[i]->type == 'E')
		return (display->map->img_exit);
	else if (display->map->tiles[i]->type == 'P')
		return (display->map->img_player);
	else if (display->map->tiles[i]->type == '1')
		return (display->map->img_wall);
	else
		return (display->map->img_death);
}

int	ft_loop_hook(t_display *display)
{
	static int	i = -1;
	static int	frames_counter = 0;
	void		*img_ptr;

	if (display->map->player_is_moving >= 0)
	{
		if (frames_counter <= 3)
			change_player_img(display, frames_counter);
		++frames_counter;
	}
	mlx_clear_window(display->mlx, display->win);
	while (++i < (display->map->height * display->map->width))
	{
		img_ptr = get_img_to_put(display, i);
		mlx_put_image_to_window(display->mlx, display->win, img_ptr,
			display->map->tiles[i]->x * 32, display->map->tiles[i]->y * 32);
	}
	i = -1;
	if (frames_counter > 3)
		frames_counter = 0;
	return (0);
}
