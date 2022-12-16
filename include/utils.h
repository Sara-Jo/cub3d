/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 01:39:50 by hossong           #+#    #+#             */
/*   Updated: 2022/12/16 16:59:46 by hossong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

void	exit_with_error(char *str);
char	*ft_strndup(const char *s1, int n);
char	*get_next_line(int fd);
int		ft_isspace(int c);
void	free_str(char **str);
void	exit_with_error(char *str);
int		ft_wordcount(char const *s, char *deli);
char	*ft_firstword(const char *s, char *deli);
char	**ft_inside_split(char const *s, char *deli, int nbr_of_words);
char	**ft_split_str(char const *s, char *deli);

#endif
