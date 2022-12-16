# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/06 19:45:50 by hossong           #+#    #+#              #
#    Updated: 2022/12/15 21:36:22 by hossong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CFLAGS = -Wall -Werror -Wextra -fsanitize=address
SRCS = main.c utils.c render.c load.c hook.c vec.c player.c wall.c
SRCS_DIR = srcs
OBJS_DIR = objs
OBJS = $(SRCS:%.c=%.o)
OBJECTS = $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS))
DEPS = $(OBJS:%.o=%.d)
DEPENDS = $(patsubst %.d, $(OBJS_DIR)/%.d, $(DEPS))

LIBFT = lib/libft/libft.a
MINILIBX = lib/minilibx/libmlx.a
INCLUDE = -I include/ -I $(dir $(LIBFT)) -I $(dir $(MINILIBX))
LIB = -L $(dir $(LIBFT)) -lft -framework OpenGL -framework AppKit \
		-L $(dir $(MINILIBX)) -lmlx -lm

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
	 @rmdir -p $(OBJS_DIR)

fclean : clean
	$(RM) $(NAME)
	 @make -C $(dir $(MINILIBX)) clean
	 @make -C $(dir $(LIBFT)) fclean

re	:
	@make fclean
	@make all

-include $(DEPENDS)
