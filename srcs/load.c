/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:40:00 by hossong           #+#    #+#             */
/*   Updated: 2022/12/16 19:43:57 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "utils.h"
#include "map.h"
#include <math.h>

void	validate_color_data(char **color_data)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (color_data[i][j])
		{
			if (!ft_isdigit(color_data[i][j]))
				exit_with_error("Invalid color data\n");
			j++;
		}
		tmp = ft_atoi(color_data[i]);
		if (tmp < 0 || tmp > 255)
			exit_with_error("Invalid color data\n");
		i++;
	}
}

void	set_color_data(char type, char *val, t_data *data)
{
	char	**split_data;
	int		i;

	i = 0;
	split_data = ft_split(val, ',');
	while (split_data[i])
		i++;
	if (i != 3)
		exit_with_error("Invalid color data\n");
	validate_color_data(split_data);
	if (type == 'F')
	{
		data->f_color.r = ft_atoi(split_data[0]);
		data->f_color.g = ft_atoi(split_data[1]);
		data->f_color.b = ft_atoi(split_data[2]);
	}
	else if (type == 'C')
	{
		data->c_color.r = ft_atoi(split_data[0]);
		data->c_color.g = ft_atoi(split_data[1]);
		data->c_color.b = ft_atoi(split_data[2]);
	}
	free_str(split_data);
	free(val);
}

static void	set_info_data(char *type, char *val, t_data *data)
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
		exit_with_error("Invalid map info\n");
}

static int	is_elements_complete(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (data->texture[i] == NULL)
			return (0);
		i++;
	}
	if (data->c_color.r == -1 || data->c_color.g == -1 \
		|| data->c_color.b == -1 || data->f_color.r == -1 \
		|| data->f_color.g == -1 || data->f_color.b == -1)
		return (0);
	return (1);
}

void	validate_data(char **raw, t_data *data)
{
	int		i;
	int		j;
	char	**split_data;

	i = -1;
	split_data = NULL;
	while (raw[++i])
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
			exit_with_error("Invalid map info\n");
		set_info_data(split_data[0], split_data[1], data);
		free_str(split_data);
	}
	check_map(data, &raw[i]);
}
