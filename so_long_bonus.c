/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 09:28:31 by mprofett          #+#    #+#             */
/*   Updated: 2023/02/10 09:25:29 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	init_map(t_display *display, char *map_name)
{
	t_tile_datas	*pos;
	int				collectibles;
	int				i;

	display->map = malloc(sizeof(t_map));
	if (!display->map)
		strerror_and_exit(display, "malloc map");
	get_map_values(display, map_name);
	i = -1;
	while (++i < (display->map->width * display->map->height))
		if (display->map->tiles[i]->type == 'P')
			pos = display->map->tiles[i];
	collectibles = display->map->nbr_collectibles;
	display->map_is_initialized = 1;
	if (valid_path_on_map(display, pos) == 0)
		map_error_and_exit(display, "No valid path for this map");
	display->map->nbr_collectibles = collectibles;
	display->map->nbr_exit = 1;
	display->map->player_is_moving = -1;
}

void	init_display(t_display *display, char *map_name)
{
	display->win = NULL;
	display->moves = NULL;
	display->moves_set = NULL;
	display->player_set = NULL;
	display->map = NULL;
	display->map_is_initialized = 0;
	display->textures_and_sprites_initialized = 0;
	display->mlx = mlx_init();
	if (!display->mlx)
		strerror_and_exit(display, "mlx_init");
	init_map(display, map_name);
	if (display->map->width > 80 || display->map->height > 43)
		map_error_and_exit(display, "Map too wide for s19 Mac resolution");
	init_sprites(display);
	init_textures(display, 32, 32);
	display->textures_and_sprites_initialized = 1;
	display->win = mlx_new_window(display->mlx, display->map->width * 32,
			display->map->height * 32, "so_long");
	if (!display->win)
		strerror_and_exit(display, "mlx_new_window");
}

void	check_args(int argc, char **argv)
{
	int	i;

	if (argc != 2)
	{
		ft_printf("Wrong arguments number\n");
		exit (EXIT_FAILURE);
	}
	i = ft_strlen(argv[1]) - 4;
	if (argv[1][i] != '.' || argv[1][i + 1] != 'b'
		|| argv[1][i + 2] != 'e' || argv[1][i + 3] != 'r')
	{
		ft_printf("Wrong map file extension\n");
		exit (EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
	t_display	*display;

	check_args(argc, argv);
	display = malloc(sizeof(t_display));
	if (!display)
	{
		ft_printf("Error on malloc display: %s", strerror(errno));
		exit(EXIT_FAILURE);
	}
	init_display(display, argv[1]);
	mlx_loop_hook (display->mlx, &ft_loop_hook, display);
	mlx_key_hook (display->win, &ft_key_hook, display);
	mlx_hook(display->win, 17, 0, &ft_mlx_hook, display);
	mlx_hook(display->win, 2, 0, &ft_key_hook, display);
	mlx_loop(display->mlx);
	return (0);
}
