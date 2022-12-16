/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjo <sjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 01:39:50 by hossong           #+#    #+#             */
/*   Updated: 2022/12/16 19:28:42 by sjo              ###   ########.fr       */
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

// utils1.c
char	*get_next_line(int fd);
int		ft_isspace(int c);
int		create_rgb(int r, int g, int b);

// utils2.c
void	free_str(char **str);
char	*ft_strndup(const char *s1, int n);
void	exit_with_error(char *str);
int		access_file(char *file);

// ft_split_str.c
char	**ft_freeall(char **s);
int		ft_wordcount(char const *s, char *deli);
char	*ft_firstword(const char *s, char *deli);
char	**check_firstword(char const *s, char *deli, int nbr_of_words, \
							char **ptr);
char	**ft_inside_split(char const *s, char *deli, int nbr_of_words);
char	**ft_split_str(char const *s, char *deli);

#endif
