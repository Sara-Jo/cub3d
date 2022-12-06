# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/06 19:45:50 by hossong           #+#    #+#              #
#    Updated: 2022/12/06 21:09:53 by hossong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CFLAGS = -Wall -Werror -Wextra -g3
SRCS = main.c utils.c
OBJS = $(SRCS:%.c=%.o)
LIBFT = lib/libft/libft.a
MINILIBX = lib/minilibx/libmlx.a
INCLUDE = -I. -I $(dir $(LIBFT)) -I $(dir $(MINILIBX))
LIB = -L $(dir $(LIBFT)) -lft -L $(dir $(MINILIBX)) -lmlx -framework OpenGL -framework AppKit

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

all :
	@make -C $(dir $(MINILIBX))
	@make -C $(dir $(LIBFT))
	@make $(NAME)

$(NAME) : $(OBJS) $(LIBFT) $(MINILIBX)
	$(CC) $(CFLAGS) $^ -o $@ $(LIB)

clean :
	$(RM) $(OBJS)

fclean :
	@make clean
	$(RM) $(NAME)

re	:
	@make fclean
	@make $(NAME)
