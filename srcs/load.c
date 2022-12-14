/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjo <sjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:40:00 by hossong           #+#    #+#             */
/*   Updated: 2022/12/14 19:27:47 by sjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>
#include <math.h>

int	access_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(file);
		return (-1);
	}
	if (ft_strncmp(ft_strrchr(file, '.'), ".cub", 5) != 0)
	{
		ft_putstr_fd("Error\n", 2);
		return (-1);
	}
	return (fd);
}

char	**file_to_rawdata(int fd, int depth)
{
	char	**des;
	char	*line;

	des = NULL;
	line = get_next_line(fd);
	if (line == NULL)
		des = (char **)malloc(sizeof(char *) * (depth + 1));
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
		map = (char **)malloc(sizeof(char *) * (depth + 1));
	else
		map = load_map(raw + 1, depth + 1);
	if (map)
	{
		map[depth] = NULL;
		if (*raw)
			map[depth] = ft_strdup(*raw);
	}
	return (map);
}

// TODO 1: 6가지 유효한 문자인지 체크
// TODO 2: 벽으로 둘러싸여 있는지 체크
// TODO 3: 플레이어가 하나만 존재하는지 체크
static void	map_read(char **map, t_player *player)
{
	char	*line;
	int		x;
	int		y;

	x = 0;
	while (*map)
	{
		y = 0;
		line = *map;
		while (*line)
		{
			if (*line == 'N')
				*player = set_player(*line, x, y, 0);
			else if (*line == 'S')
				*player = set_player(*line, x, y, M_PI);
			else if (*line == 'E')
				*player = set_player(*line, x, y, M_PI / (-2.0));
			else if (*line == 'W')
				*player = set_player(*line, x, y, M_PI / 2.0);
			line++;
			y++;
		}
		x++;
		map++;
	}
}

int	validate_data(char **raw, t_data *data)
{
	int		i;
	int		count;

	i = 0;
	// TODO 1. 빈 줄, 하나 이상의 공백 처리(ft_isspace를 대체)
	// TODO 2. f_color, c_color 파싱 함수 추가 
	// TODO 3. 6가지 모두 잘 들어왔는지
	while (raw[i])
	{
		if (count == 6)
			break ;
		if (ft_strnstr(raw[i], "NO", 2) && ft_isspace(*(raw[i] + 2)))
		{
			data->texture[0] = ft_strtrim(raw[i] + 3, "\n");
			count++;
		}
		else if (ft_strnstr(raw[i], "SO", 2) && ft_isspace(*(raw[i] + 2)))
		{
			data->texture[1] = ft_strtrim(raw[i] + 3, "\n");
			count++;
		}
		else if (ft_strnstr(raw[i], "WE", 2) && ft_isspace(*(raw[i] + 2)))
		{
			data->texture[2] = ft_strtrim(raw[i] + 3, "\n");
			count++;
		}
		else if (ft_strnstr(raw[i], "EA", 2) && ft_isspace(*(raw[i] + 2)))
		{
			data->texture[3] = ft_strtrim(raw[i] + 3, "\n");
			count++;
		}
		else if (ft_strnstr(raw[i], "F", 1) && ft_isspace(*(raw[i] + 1)))
		{
			data->f_color = 1;
			count++;
		}
		else if (ft_strnstr(raw[i], "C", 1) && ft_isspace(*(raw[i] + 1)))
		{
			data->c_color = 1;
			count++;
		}
		else {
			printf("Invalid map\n");
			exit(1);
		}
			
		i++;
	}
	data->map = load_map(&raw[i], 0);
	map_read(data->map, &data->player);
	return (0);
}
