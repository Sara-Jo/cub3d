/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:40:00 by hossong           #+#    #+#             */
/*   Updated: 2022/12/10 02:00:06 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>

int	access_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(file);
		return (-1);
	}
	if (ft_strncmp(ft_strchr(file, '.'), ".cub", 5) != 0)
	{
		ft_putstr_fd("no .cub\n", 2);
		return (-1);
	}
	return (fd);
}

char	**file_to_rawdata(int fd, int depth)
{
	char	**des;
	char	*line;

	des = 0;
	line = get_next_line(fd);
	if (line == NULL)
		des = (char **)malloc(sizeof(char *) * depth);
	else
		des = file_to_rawdata(fd, depth + 1);
	if (des)
		des[depth] = line;
	return (des);
}

static char	**load_map(char **raw, int depth)
{
	char	**map;

	map = 0;
	if (*raw == NULL)
		map = (char **)malloc(sizeof(char *) * depth);
	else
		map = load_map(raw + 1, depth + 1);
	if (map)
		map[depth] = *raw;
	return (map);
}

static void	map_read(char **map, t_player *player)
{
	char *line;
	int	x;
	int y;
	y = 0;
	while (*map)
	{
		x = 0;
		line = *map;
		while (*line)
		{
			if (*line == 'N')
			{
				player->player_dir = *line;
				player->row = y;
				player->col = x;
				player->dir.x = -1;
				player->dir.y = 0;
				player->plane.x = 0;
				player->plane.y = 0.66;
			}
			else if (*line == 'S')
			{
				player->player_dir = *line;
				player->row = y;
				player->col = x;
				player->dir.x = 1;
				player->dir.y = 0;
				player->plane.x = 0;
				player->plane.y = -0.66;
			}
			else if (*line == 'E')
			{
				player->player_dir = *line;
				player->row = y;
				player->col = x;
				player->dir.x = 0;
				player->dir.y = -1;
				player->plane.x = 0.66;
				player->plane.y = 0;
			}
			else if (*line == 'W')
			{
				player->player_dir = *line;
				player->row = y;
				player->col = x;
				player->dir.x = 0;
				player->dir.y = 1;
				player->plane.x = -0.66;
				player->plane.y = 0;
			}
			line++;
			x++;
		}
		y++;
		map++;
	}
}

int	validate_data(char **raw, t_data *data)
{
	int		i;

	i = 0;
	while (raw[i] && i < 6)
	{
		if (ft_strnstr(raw[i], "NO", 2) && ft_isspace(*(raw[i] + 2)))
			data->texture_no = raw[i];
		else if (ft_strnstr(raw[i], "SO", 2) && ft_isspace(*(raw[i] + 2)))
			data->texture_so = raw[i];
		else if (ft_strnstr(raw[i], "WE", 2) && ft_isspace(*(raw[i] + 2)))
			data->texture_we = raw[i];
		else if (ft_strnstr(raw[i], "EA", 2) && ft_isspace(*(raw[i] + 2)))
			data->texture_ea = raw[i];
		else if (ft_strnstr(raw[i], "F", 1) && ft_isspace(*(raw[i] + 1)))
			data->f_color = 1;
		else if (ft_strnstr(raw[i], "C", 1) && ft_isspace(*(raw[i] + 1)))
			data->c_color = 1;
		i++;
	}
	data->map = load_map(&raw[i], 0);
	free(raw);
	map_read(data->map, &data->player);
	return (0);
}