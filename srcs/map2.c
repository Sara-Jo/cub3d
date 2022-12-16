/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:03:33 by hossong           #+#    #+#             */
/*   Updated: 2022/12/16 16:16:29 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
		exit_with_error("Error: Invalid map\n");
	if (player->player_dir && ft_strchr("NSEW", c))
		exit_with_error("Error: Invalid map\n");
	if (c == 'N')
		*player = set_player(c, x, y, 0);
	else if (c == 'S')
		*player = set_player(c, x, y, M_PI);
	else if (c == 'E')
		*player = set_player(c, x, y, M_PI / (-2.0));
	else if (c == 'W')
		*player = set_player(c, x, y, M_PI / 2.0);
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
			map_line_valid_symbol(*line, player, x, y);
			line++;
			y++;
		}
		x++;
		map++;
	}
}
