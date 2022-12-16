/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:40:00 by hossong           #+#    #+#             */
/*   Updated: 2022/12/16 15:16:02 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "utils.h"
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
		exit_with_error("Invalid file type\n");
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
	{
		if (line && ft_strchr(line, '\n'))
			des[depth] = ft_strndup(line, ft_strlen(line) - 1);
		else if (line)
			des[depth] = ft_strdup(line);
		else
			des[depth] = NULL;
		if (line)
			free(line);
	}
	return (des);
}

void	map_read(char **map, t_player *player)
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
			if (ft_strchr("01NSEW \t\r\n\v\f", *line) == NULL)
				exit_with_error("Error: Invalid map\n");
			if (player->player_dir && ft_strchr("NSEW", *line))
				exit_with_error("Error: Invalid map\n");
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

void set_color_data(char type, char *val, t_data *data)
{
	char **split_data;
	int i;
	int j;
	int tmp[3];

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
		while (split_data[i][j])
		{
			if (!ft_isdigit(split_data[i][j]))
				exit_with_error("Error: Invalid color data\n");
			j++;
		}
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

int is_elements_complete(t_data *data)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (data->texture[i] == NULL)
			return (0);
		i++;
	}
	if (data->c_color.r == -1 || data->c_color.g == -1 || data->c_color.b == -1 || data->f_color.r == -1 || data->f_color.g == -1 || data->f_color.b == -1)
		return (0);
	return (1);
}

int validate_data(char **raw, t_data *data)
{
	int		i;
	int		j;
	char	**split_data;

	i = 0;
	while (i < 6)
	{
		if (raw[i] && *raw[i] == '\0')
		{
			i++;
			continue ;
		}
		if (is_elements_complete(data))
			break ;
		split_data = ft_split_str(raw[i], " \t\n\v\f\r");
		j = 0;
		while (split_data[j])
			j++;
		if (j != 2)
			exit_with_error("Error: Invalid map info\n");
		set_info_data(split_data[0], split_data[1], data);
		i++;
	}
	while (raw[i] && *raw[i] == '\0')
		i++;
	if (raw[i] == NULL)
	{
		ft_putstr_fd("Invalid map\n", 2);
		return (-1);
	}
	validate_map(data, &raw[i]);
	map_read(data->map, &data->player);
	free_str(split_data);
	return (0);
}
