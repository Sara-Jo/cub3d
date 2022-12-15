/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:55:15 by hossong           #+#    #+#             */
/*   Updated: 2022/12/16 01:49:04 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "mlx.h"
#include <stdio.h>

void	clear_plat_data(t_data *a)
{
	if (a->img.ptr)
		mlx_destroy_image(a->sc.mlx, a->img.ptr);
	if (a->sc.mlx_win)
		mlx_clear_window(a->sc.mlx, a->sc.mlx_win);
	if (a->sc.mlx)
		mlx_destroy_window(a->sc.mlx, a->sc.mlx_win);
}

void	clear_exec_data(t_data *a)
{
	int	i;

	if (a->map)
		free_str(a->map);
	i = 0;
	if (a->tex_addr)
	{
		i = 0;
		while (i < 4)
		{
			if (a->tex_addr[i])
				free(a->tex_addr[i]);
			i++;
		}
		free(a->tex_addr);
	}
	while (i < 4)
	{
		if (a->texture[i])
			free(a->texture[i]);
		i++;
	}
}

void	load_data(t_data *data, char *argv)
{
	char	**raw;
	int		fd;

	fd = access_file(argv);
	if (fd == -1)
	{
		clear_exec_data(data);
		clear_plat_data(data);
		exit(1);
	}
	raw = file_to_rawdata(fd, 0);
	close(fd);
	if (validate_data(raw, data) == -1)
	{
		clear_exec_data(data);
		clear_plat_data(data);
		ft_putstr_fd("Error\n", 2);
		exit(1);
	}
	free_str(raw);
	load_texture(data);
}

t_data	init_data(void)
{
	t_data	new;

	ft_memset(&new, 0, sizeof(t_data));
	new.sc.mlx = mlx_init();
	new.sc.mlx_win = mlx_new_window(new.sc.mlx, WIDTH, HEIGHT, "cub3d");
	new.img.ptr = mlx_new_image(new.sc.mlx, WIDTH, HEIGHT);
	new.img.addr = mlx_get_data_addr(new.img.ptr, &new.img.bits_per_pixel, \
									 &new.img.line_length, &new.img.endian);
	new.f_color.r = -1;
	new.f_color.g = -1;
	new.f_color.b = -1;
	new.c_color.r = -1;
	new.c_color.g = -1;
	new.c_color.b = -1;
	return (new);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		exit_with_error("Error: Map file not entered\n");
	data = init_data();
	load_data(&data, argv[1]);
	render(&data);
	mlx_hook(data.sc.mlx_win, X_EVENT_KEY_PRESS, 0, &handle_key_down, &data);
	mlx_hook(data.sc.mlx_win, X_EVENT_KEY_EXIT, 0, &handle_exit, &data);
	mlx_loop(data.sc.mlx);
	return (0);
}
