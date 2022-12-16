/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:13:41 by hossong           #+#    #+#             */
/*   Updated: 2022/12/16 20:00:37 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "main.h"

char	**load_map(char **raw, int depth);
void	map_read(char **map, t_player *player);
void	check_map(t_data *a, char **raw);
int		valid_char(char c);

#endif
