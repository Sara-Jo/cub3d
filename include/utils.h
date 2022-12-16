/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 01:39:50 by hossong           #+#    #+#             */
/*   Updated: 2022/12/16 01:46:30 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOAD_H
# define LOAD_H

void	exit_with_error(char *str);
char	*ft_strndup(const char *s1, int n);
char	*get_next_line(int fd);
int		ft_isspace(int c);
void	free_str(char **str);

#endif
