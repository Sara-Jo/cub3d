/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:55:15 by hossong           #+#    #+#             */
/*   Updated: 2022/12/13 13:03:57 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "mlx.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		fd;
	char	**raw;

	if (argc != 2)
		return (1);
	fd = access_file(argv[1]);
	if (fd == -1)
		return (1);
	raw = file_to_rawdata(fd, 0);
	close(fd);
	if (validate_data(raw, &data) == -1)
	{
		ft_putstr_fd("validate_data error\n", 2);
		return (1);
	}
	data.sc.mlx = mlx_init();
	load_texture(&data);
	data.sc.mlx_win = mlx_new_window(data.sc.mlx, WIDTH, HEIGHT, "hi");
	data.img.ptr = mlx_new_image(data.sc.mlx, WIDTH, HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.ptr, &data.img.bits_per_pixel, \
									&data.img.line_length, &data.img.endian);
	render(&data);
	mlx_hook(data.sc.mlx_win, 2, 0, &handle_key_down, &data);
	mlx_loop(data.sc.mlx);
	return (0);
}
