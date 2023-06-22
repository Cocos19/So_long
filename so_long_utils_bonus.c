/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:10:13 by mprofett          #+#    #+#             */
/*   Updated: 2023/02/10 08:53:46 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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

void	update_tiles(t_display *display, t_tile_datas *next_pos)
{
	if (next_pos->type == 'C')
		--display->map->nbr_collectibles;
	if (display->map->nbr_collectibles == 0 && next_pos->type == 'E')
	{
		ft_printf("You win\n");
		free_display(display);
		exit(EXIT_SUCCESS);
	}
	display->map->player->type = '0';
	next_pos->type = 'P';
	display->map->player = next_pos;
	display->map->player_is_moving = -1;
}

void	update_player_pos(t_display *display, t_tile_datas *new_p, int key)
{
	if (new_p && new_p->type == 'D')
	{
		ft_printf("You died\n");
		free_display(display);
		exit(EXIT_SUCCESS);
	}
	if (new_p && new_p->type != '1' && !(new_p->type == 'E'
			&& display->map->nbr_collectibles > 0))
	{
		display->map->player_next_pos = new_p;
		display->map->player_is_moving = key;
		++display->nbr_moves;
		if (display->nbr_moves > 1000)
		{
			ft_printf("You died\n");
			free_display(display);
			exit(EXIT_SUCCESS);
		}
		free(display->moves);
		display->moves = ft_itoa(display->nbr_moves);
		if (!display->moves)
			strerror_and_exit(display, "malloc moves display");
	}
}
