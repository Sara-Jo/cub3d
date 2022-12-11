# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/06 19:45:50 by hossong           #+#    #+#              #
#    Updated: 2022/12/11 16:25:05 by hossong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CFLAGS = -Wall -Werror -Wextra -g3
SRCS = main.c utils.c render.c load.c hook.c vec.c player.c
SRCS_DIR = srcs
OBJS_DIR = objs
OBJS = $(SRCS:%.c=%.o)
OBJECTS = $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS))
DEPS = $(OBJS:%.o=%.d)
DEPENDS = $(patsubst %.d, $(OBJS_DIR)/%.d, $(DEPS))

LIBFT = lib/libft/libft.a
MINILIBX = lib/minilibx/libmlx.a
INCLUDE = -I. -I $(dir $(LIBFT)) -I $(dir $(MINILIBX))
LIB = -L $(dir $(LIBFT)) -lft -L $(dir $(MINILIBX)) -lmlx -framework OpenGL -framework AppKit -lm

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE) -MMD

all :
	@make -C $(dir $(MINILIBX))
	@make -C $(dir $(LIBFT))
	@make $(NAME)

$(NAME) : $(OBJECTS) $(LIBFT) $(MINILIBX)
	$(CC) $(CFLAGS) $^ -o $@ $(LIB)

clean :
	$(RM) $(OBJECTS) $(DEPENDS)
	@rmdir $(OBJS_DIR)

fclean : clean
	$(RM) $(NAME)

re	:
	@make fclean
	@make -C $(dir $(MINILIBX)) fclean
	@make -C $(dir $(LIBFT)) fclean
	@make all

-include $(DEPENDS)