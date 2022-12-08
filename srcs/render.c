/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:33:08 by hossong           #+#    #+#             */
/*   Updated: 2022/12/08 21:10:38 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "libft.h"
#include "mlx.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	view_north(t_data *a)
{
	int player_row = a->player.row;
	int distance_from_player;
	int i = 0;

	// row: player_row 부터 0번째 row까지 탐색
	while (player_row) {
		// col: 처음부터 끝까지 탐색
		while (i < screenWidth) {
			if (a->map[player_row][i] == '1') {
				distance_from_player = a->player.row - player_row;
				my_mlx_pixel_put(&a->img, player_row, i, 0xff0000);
			}
			else if (a->map[player_row][i] == '0')
				my_mlx_pixel_put(&a->img, player_row, i, 0x00ff00);
			// else if (a->map[y][x] == 'N')
			//	 my_mlx_pixel_put(&a->img, x, y, 0x0000ff);
			i++;
		}
		player_row--;
	}

}

void	render(t_data *a)
{
	int	i;
	int	j;

	ft_bzero(a->img.addr, screenWidth * screenHeight * a->img.bits_per_pixel / 8);
	// a->view = player_veiw(a);
	j = 0;
	while (j < screenHeight)
	{
		i = 0;
		while (i < screenWidth)
		{
			
			my_mlx_pixel_put(&a->img, i, j, 0x00002f);
			// if (a->player_dir == 'N')
			//	 view_north(a, i, j);
			// else if (a->player_dir == 'S')
			//	 view_south(a);
			// else if (a->player_dir == 'E')
			//	 view_east(a);
			// else if (a->player_dir == 'W')
			//	 view_west(a);
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(a->sc.mlx, a->sc.mlx_win, a->img.ptr, 0, 0);
}