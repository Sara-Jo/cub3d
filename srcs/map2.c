/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:03:33 by hossong           #+#    #+#             */
/*   Updated: 2022/12/18 14:07:09 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	valid_char(char c)
{
	return (c == '0' || c == 'N' || c == 'W' || c == 'E' || c == 'S');
}

char	**load_map(char **raw, int depth)
{
	char	**map;

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

static void	map_line_valid_symbol(char c, t_player *player, int x, int y)
{
	if (ft_strchr("01NSEW \t\r\n\v\f", c) == NULL)
		exit_with_error("Invalid map\n");
	if (player->player_dir && ft_strchr("NSEW", c))
		exit_with_error("Invalid map\n");
	if (c == 'N')
		*player = set_player(c, x, y, 0);
	else if (c == 'S')
		*player = set_player(c, x, y, M_PI);
	else if (c == 'E')
		*player = set_player(c, x, y, M_PI / 2.0);
	else if (c == 'W')
		*player = set_player(c, x, y, M_PI / (-2.0));
}

void	map_read(char **map, t_player *player)
{
	char	*line;
	int		x;
	int		y;

	y = 0;
	while (*map)
	{
		line = *map;
		x = 0;
		while (*line)
		{
			map_line_valid_symbol(*line, player, x, y);
			line++;
			x++;
		}
		y++;
		map++;
	}
	if (!player->player_dir)
		exit_with_error("Invalid map\n");
}
