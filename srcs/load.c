/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:40:00 by hossong           #+#    #+#             */
/*   Updated: 2022/12/15 15:38:45 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>
#include <math.h>

int access_file(char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(file);
		return (-1);
	}
	if (ft_strncmp(ft_strrchr(file, '.'), ".cub", 5) != 0)
	{
		exit_with_error("Invalid file type\n");
		// ft_putstr_fd("Error\n", 2);
		// return (-1);
	}
	return (fd);
}

char **file_to_rawdata(int fd, int depth)
{
	char **des;
	char *line;

	des = NULL;
	line = get_next_line(fd);
	if (line == NULL)
		des = (char **)malloc(sizeof(char *) * (depth + 1));
	else
		des = file_to_rawdata(fd, depth + 1);
	if (des)
	{
		if (line && ft_strchr(line, '\n'))
			des[depth] = ft_strndup(line, ft_strlen(line) - 1);
		else if (line)
			des[depth] = ft_strdup(line);
		else
			des[depth] = NULL;
	}
	return (des);
}

static char **load_map(char **raw, int depth)
{
	char **map;

	map = 0;
	if (*raw == NULL)
		map = (char **)malloc(sizeof(char *) * (depth + 1));
	else
		map = load_map(raw + 1, depth + 1);
	if (map)
	{
		if (*raw)
			map[depth] = ft_strdup(*raw);
		else
			map[depth] = NULL;
	}
	return (map);
}

// TODO 1: 6가지 유효한 문자인지 체크
// TODO 2: 벽으로 둘러싸여 있는지 체크
// TODO 3: 플레이어가 하나만 존재하는지 체크
static void map_read(char **map, t_player *player)
{
	char *line;
	int x;
	int y;

	x = 0;
	while (*map)
	{
		y = 0;
		line = *map;
		// if (ft_strchr("01NSEW ", line) == NULL)
		// 	exit_with_error("Error: Invalid map\n");
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

void	check_row(t_data *a, char *map_line)
{
	int	i;

	i = 0;
	while (ft_isspace(map_line[i]))
		i++;
	while (map_line[i] == '1')
		i++;
	
	while (i < a->map_width)
	{
		while (ft_isspace(map_line[i]))
			i++;
		i++;
	}
}

void	check_map(t_data *a)
{
	int		i;
	int		width;
	char	*line;

	i = 0;
	while (a->map[i] != NULL)
	{
		width = ft_strlen(a->map[i]);
		if (a->map_width < width)
			a->map_width = width;
		i++;
	}
	a->map_height = i - 1;
	i = 0;
	while (i < a->map_height)
	{
		width = ft_strlen(a->map[i]);
		if (width < a->map_width)
		{ // fill_map_width
			int j = 0;
			line = (char *)malloc(sizeof(char) * (a->map_width + 1));
			if (!line)
				exit(1);
			ft_strlcpy(line, a->map[i], width + 1);
			j = width;
			while (j < a->map_width)
			{
				line[j] = '1';
				j++;
			}
			line[j] = '\0';
			free(a->map[i]);
			a->map[i] = line;
		}
		check_row(a, a->map[i]);
		i++;
	}
}


void set_color_data(char type, char *val, t_data *data)
{
	char **split_data;
	int i;
	int j;
	int tmp[3];

	type = 'a';
	data->f_color.r = 0;

	i = 0;
	split_data = ft_split(val, ',');
	while (split_data[i])
		i++;
	if (i != 3)
		exit_with_error("Error: Invalid color data\n");
	i = 0;
	while (i < 3)
	{
		j = 0;
		// 예외 처리 필요
		// while (split_data[i][j])
		// {
		// 	if (!ft_isdigit(split_data[i][j]))
		// 		exit_with_error("Error: Invalid color data: isdigit error\n");
		// 	j++;
		// }
		tmp[i] = ft_atoi(split_data[i]);
		if (tmp[i] < 0 || tmp[i] > 255)
			exit_with_error("Error: Invalid color data\n");
		i++;
	}
	if (type == 'F')
	{
		data->f_color.r = tmp[0];
		data->f_color.g = tmp[1];
		data->f_color.b = tmp[2];
	}
	else if (type == 'C')
	{
		data->c_color.r = tmp[0];
		data->c_color.g = tmp[1];
		data->c_color.b = tmp[2];
	}
}

void set_info_data(char *type, char *val, t_data *data)
{
	if (ft_strncmp(type, "NO", 3) == 0)
		data->texture[0] = ft_substr(val, 0, ft_strlen(val));
	else if (ft_strncmp(type, "SO", 3) == 0)
		data->texture[1] = ft_substr(val, 0, ft_strlen(val));
	else if (ft_strncmp(type, "WE", 3) == 0)
		data->texture[2] = ft_substr(val, 0, ft_strlen(val));
	else if (ft_strncmp(type, "EA", 3) == 0)
		data->texture[3] = ft_substr(val, 0, ft_strlen(val));
	else if (ft_strncmp(type, "F", 2) == 0)
		set_color_data('F', ft_substr(val, 0, ft_strlen(val)), data);
	else if (ft_strncmp(type, "C", 2) == 0)
		set_color_data('C', ft_substr(val, 0, ft_strlen(val)), data);
	else
		exit_with_error("Error: Invalid map info\n");
}

void validate_elements(t_data *data)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (data->texture[i] == NULL)
			exit_with_error("Error: Texture is empty\n");
		i++;
	}
	i = 0;
	if (data->c_color.r == -1 || data->c_color.g == -1 || data->c_color.b == -1 || data->f_color.r == -1 || data->f_color.g == -1 || data->f_color.b == -1)
		exit_with_error("Error: Color is empty\n");
	i++;
}

int validate_data(char **raw, t_data *data)
{
	int i;
	int j;
	// int count;
	char **split_data;

	i = 0;
	// TODO 1. 빈 줄, 하나 이상의 공백 처리(ft_isspace를 대체)
	// TODO 2. f_color, c_color 파싱 함수 추가
	// TODO 3. 6가지 모두 잘 들어왔는지
	while (i < 6)
	{
		// while (ft_isspace(raw[i][j]))
		// 	j++;
		split_data = ft_split(raw[i], ' ');
		j = 0;
		while (split_data[j])
			j++;
		if (j != 2)
			exit_with_error("Error: Invalid map info\n");
		set_info_data(split_data[0], split_data[1], data);
		i++;
	}
	while (raw[i] && *(raw[i]) == '\0')
		i++;
	if (raw[i] == NULL)
	{
		ft_putstr_fd("Invalid map\n", 2);
		return (-1);
	}
	data->map = load_map(&raw[i], 0);
	check_map(data);
	map_read(data->map, &data->player);
	free_str(split_data);
	return (0);
}
