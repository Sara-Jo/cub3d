/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:56:04 by hossong           #+#    #+#             */
/*   Updated: 2022/12/06 21:44:01 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <fcntl.h>

typedef struct s_data
{
	char	*texture_ea;
	char	*texture_we;
	char	*texture_so;
	char	*texture_no;
	int		f_color;
	int		c_color;
	char	**map;
	int		map_width;
	int		map_height;
	int		fd;
}	t_data;

char	*get_next_line(int fd);
int		ft_isspace(int c);

#endif