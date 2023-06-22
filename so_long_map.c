/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:27:25 by mprofett          #+#    #+#             */
/*   Updated: 2023/02/10 09:31:18 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_tile_datas(t_display *display, char *tiles_values, int i, int j)
{
	t_tile_datas	*new_tile_datas;

	new_tile_datas = malloc(sizeof(t_tile_datas));
	if (!new_tile_datas)
	{
		free(tiles_values);
		strerror_and_exit(display, "malloc map tiles");
	}
	++display->map->nbr_tiles;
	new_tile_datas->x = i - ((j - 1) * display->map->width);
	new_tile_datas->y = j - 1;
	new_tile_datas->tile_nbr = i;
	new_tile_datas->type = tiles_values[i];
	if (tiles_values[i] == '1' || tiles_values[i] == 'E')
		new_tile_datas->is_accessible = 0;
	else
		new_tile_datas->is_accessible = 1;
	display->map->tiles[i] = new_tile_datas;
	if (tiles_values[i] == 'P')
		display->map->player = display->map->tiles[i];
}

void	init_tiles(t_display *display, char *tiles_values)
{
	int	i;
	int	j;

	i = -1;
	j = 1;
	while (++i < display->map->width * j)
	{
		if (i < display->map->width || i == display->map->width * j
			|| i == (display->map->width * j) - 1 || i >= (display->map->width
				* display->map->height) - display->map->width)
			if (tiles_values[i] != '1')
				map_error_and_exit(display, "Map not surrounded by walls");
		if (tiles_values[i] == 'C')
			++display->map->nbr_collectibles;
		else if (tiles_values[i] == 'P')
			++display->map->nbr_player;
		else if (tiles_values[i] == 'E')
			++display->map->nbr_exit;
		else if (!(tiles_values[i] == '0' || tiles_values[i] == '1'))
			map_error_and_exit(display, "Invalid character on map file");
		get_tile_datas(display, tiles_values, i, j);
		if (i == (display->map->width * j) - 1 && j < display->map->height)
			++j;
	}
}

int	valid_path_on_map(t_display *display, t_tile_datas *pos)
{
	if (display->map->nbr_exit == 0 && display->map->nbr_collectibles == 0)
		return (1);
	if (pos->type == 'E')
		--display->map->nbr_exit;
	if (pos->is_accessible == 0)
		return (0);
	else if (pos->type == 'C')
		--display->map->nbr_collectibles;
	pos->is_accessible = 0;
	if (pos->y > 1)
		valid_path_on_map(display, display->map->tiles[pos->tile_nbr
			- display->map->width]);
	if (pos->x < display->map->width - 2)
		valid_path_on_map(display, display->map->tiles[(pos->tile_nbr + 1)]);
	if (pos->x > 1)
		valid_path_on_map(display, display->map->tiles[(pos->tile_nbr - 1)]);
	if (pos->y < display->map->height - 2)
		valid_path_on_map(display, display->map->tiles[pos->tile_nbr
			+ display->map->width]);
	if (display->map->nbr_exit <= 0 && display->map->nbr_collectibles == 0)
		return (1);
	return (0);
}

void	get_map_values(t_display *display, char *map_name)
{
	char			*tiles_values;

	tiles_values = read_map(display, map_name);
	display->map->tiles = malloc(sizeof(t_tile_datas)
			* (display->map->width * display->map->height));
	if (!display->map->tiles)
		strerror_and_exit(display, "malloc tiles array");
	display->map->nbr_collectibles = 0;
	display->map->nbr_player = 0;
	display->map->nbr_exit = 0;
	display->map->nbr_tiles = 0;
	init_tiles(display, tiles_values);
	if (display->map->nbr_collectibles == 0)
		map_error_and_exit(display, "No collectibles on the map");
	if (display->map->nbr_player != 1)
		map_error_and_exit(display, "Incorrect player number number");
	if (display->map->nbr_exit != 1)
		map_error_and_exit(display, "Incorrect exit number");
	free(tiles_values);
}

char	*read_map(t_display *display, char *map_name)
{
	int		fd;
	char	*path;
	char	*tiles;

	if (ft_strncmp("maps/", map_name, 5) == 0)
		fd = open(map_name, O_RDONLY);
	else
	{
		path = ft_strjoin("maps/", map_name);
		fd = open(path, O_RDONLY);
		free(path);
	}
	if (fd < 0)
		strerror_and_exit(display, "opening map file");
	display->map->height = 0;
	tiles = get_tiles_values(display, fd);
	if (!tiles)
		map_error_and_exit(display, "empty map");
	close(fd);
	return (tiles);
}
