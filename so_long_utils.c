/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:15:16 by mprofett          #+#    #+#             */
/*   Updated: 2023/02/10 09:31:41 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_display(t_display *display)
{
	int	i;

	i = -1;
	if (display->win_is_initialized == 1)
		mlx_destroy_window(display->mlx, display->win);
	if (display->map_is_initialized == 1)
	{
		while (++i < display->map->nbr_tiles)
			if (display->map->tiles[i])
				free(display->map->tiles[i]);
		if (display->textures_is_initialized == 1)
		{
			mlx_destroy_image(display->mlx, display->map->img_collec);
			mlx_destroy_image(display->mlx, display->map->img_empty);
			mlx_destroy_image(display->mlx, display->map->img_exit);
			mlx_destroy_image(display->mlx, display->map->img_player);
			mlx_destroy_image(display->mlx, display->map->img_wall);
		}
		free(display->map);
	}
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
	ft_printf("Error on %s: %s\n", error_msg, strerror(errno));
	exit (EXIT_FAILURE);
}

char	*ft_strjoin_without_nl(char const *s1, char const *s2)
{
	char	*result;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	result = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[j] && s2[j] != '\n')
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	return (result);
}

char	*get_tiles_values(t_display *display, int fd)
{
	char	*next_line;
	char	*tiles_values;

	next_line = get_next_line(fd, 33);
	if (!next_line)
		return (NULL);
	display->map->width = ft_strlen(next_line) - 1;
	if (display->map->width < 4)
		map_error_and_exit(display, "Map too small");
	tiles_values = malloc(sizeof(char));
	if (!tiles_values)
		strerror_and_exit(display, "malloc map tiles");
	tiles_values[0] = '\0';
	while (next_line)
	{
		++display->map->height;
		tiles_values = ft_strjoin_without_nl(tiles_values, next_line);
		free(next_line);
		next_line = get_next_line(fd, 33);
		if (next_line)
			if ((int)ft_strlen(next_line) - 1 != display->map->width)
				map_error_and_exit(display, "Map is not rectangular");
	}
	return (tiles_values);
}
