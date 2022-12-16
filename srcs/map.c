/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 01:34:07 by hossong           #+#    #+#             */
/*   Updated: 2022/12/16 17:33:10 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "utils.h"
#include "map.h"

static void	valid(t_data *a, char **map, int x, int y)
{
	if ((y == 0 && map[y][x] == '0') \
		|| (y == a->map_height - 1 && map[y][x] == '0'))
		exit_with_error("Invalid map\n");
	if ((x == 0 && map[y][x] == '0') \
		|| (x == a->map_width - 1 && map[y][x] == '0'))
		exit_with_error("Invalid map\n");
	if (ft_isspace(map[y][x - 1]) || ft_isspace(map[y][x + 1]))
		exit_with_error("Invalid map\n");
	if (ft_isspace(map[y + 1][x]) || ft_isspace(map[y - 1][x]))
		exit_with_error("Invalid map\n");
	map[y][x] = '2';
	if (map[y + 1][x] == '1' && (map[y][x + 1] == '1' || map[y][x + 1] == '2'))
		return ;
	if (map[y + 1][x] && map[y + 1][x] == '0')
		valid(a, map, x, y + 1);
	if (map[y][x + 1] && map[y][x + 1] == '0')
		valid(a, map, x + 1, y);
}

static void	map_width_height(t_data *a, char **map)
{
	int		i;
	int		width;
	int		nl_count;

	i = 0;
	nl_count = 0;
	while (map[i] != NULL)
	{
		if (nl_count != 0 && ft_strchr(map[i], '1'))
			exit_with_error("Invalid map\n");
		width = ft_strlen(map[i]);
		if (width == 0 || ft_strchr(map[i], '1') == 0)
			nl_count++;
		if (a->map_width < width)
			a->map_width = width;
		i++;
	}
	a->map_height = i;
}

static void	fill_map_width(t_data *a, char **map)
{
	int		i;
	int		j;
	int		width;
	char	*line;

	i = -1;
	while (++i < a->map_height)
	{
		width = ft_strlen(map[i]);
		if (width < a->map_width)
		{
			j = 0;
			line = (char *)malloc(sizeof(char) * (a->map_width + 1));
			if (!line)
				exit_with_error("malloc\n");
			ft_strlcpy(line, map[i], width + 1);
			j = width;
			while (j < a->map_width)
				line[j++] = ' ';
			line[j] = '\0';
			free(map[i]);
			map[i] = line;
		}
	}
}

static void	validate_map(t_data *a, char **map)
{
	int		i;
	int		j;

	map_width_height(a, map);
	fill_map_width(a, map);
	a->map = load_map(map, 0);
	j = 0;
	while (j < a->map_height)
	{
		i = 0;
		while (i < a->map_width)
		{
			if (map[j][i] == '0')
				valid(a, map, i, j);
			i++;
		}
		j++;
	}
}

void	check_map(t_data *a, char **raw)
{
	int	i;

	i = 0;
	while (raw[i] && *(raw[i]) == '\0')
		i++;
	if (raw[i] == NULL)
		exit_with_error("Invalid map\n");
	validate_map(a, &raw[i]);
	map_read(a->map, &a->player);
}
