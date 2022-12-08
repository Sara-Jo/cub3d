/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 20:04:13 by sjo               #+#    #+#             */
/*   Updated: 2022/12/08 15:00:34 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"
#include "../libft/includes/libft.h"

void	error_handler(char *reason)
{
	printf("ERROR\n%s", reason);
	exit(1);
}

int	handle_exit_game(t_param *param)
{
	mlx_destroy_window(param->mlx, param->win);
	exit(0);
}

int	handle_force_exit_game(t_param *param)
{
	printf("END\n");
	handle_exit_game(param);
	return (0);
}

int	handle_complete_game(t_param *param)
{
	printf("COMPLETE\n");
	handle_exit_game(param);
	return (0);
}

void	print_move_count(int count)
{
	ft_putstr_fd("MOVE COUNT : ", 1);
	ft_putnbr_fd(count, 1);
	ft_putchar_fd('\n', 1);
}
