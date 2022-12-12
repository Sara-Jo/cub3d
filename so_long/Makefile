# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
<<<<<<< HEAD
#    By: sjo <sjo@student.42seoul.kr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/08 11:49:15 by sjo               #+#    #+#              #
#    Updated: 2022/12/07 18:32:50 by sjo              ###   ########.fr        #
=======
#    By: hossong <hossong@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/08 11:49:15 by sjo               #+#    #+#              #
#    Updated: 2022/12/08 15:04:20 by hossong          ###   ########.fr        #
>>>>>>> hossong
#                                                                              #
# **************************************************************************** #

NAME			=	so_long

LIBFTGNL_DIR	=	./libft
MLX_DIR			=	./mlx
SRCS			=	init.c	\
					map.c	\
					map2.c	\
					move.c	\
					paint_game.c	\
					so_long.c	\
					utils.c	
<<<<<<< HEAD
=======
SRCS_DIR		=	srcs
>>>>>>> hossong
OBJS_DIR		= 	objs
OBJS			=	$(SRCS:%.c=%.o)
OBJECTS			= 	$(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS))
DEPS			=	$(OBJS:%.o=%.d)
DEPENDS		 	= 	$(patsubst %.d, $(OBJS_DIR)/%.d, $(DEPS))
CLIB			=	-L$(MLX_DIR) -lmlx -L$(LIBFTGNL_DIR) -lftgnl \
					-framework OpenGL -framework AppKit

<<<<<<< HEAD
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -g3
RM				=	rm -f

$(OBJS_DIR)/%.o : %.c
=======
CFLAGS			=	-Wall -Wextra -Werror -g3

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c
>>>>>>> hossong
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MMD

all:			$(NAME)

$(NAME):		$(OBJECTS)
				$(MAKE) -C $(LIBFTGNL_DIR)
				$(MAKE) -C $(MLX_DIR)
				$(CC) $(CFLAGS) $(CLIB) $^ -o $@

clean:
				$(RM) $(OBJECTS) $(DEPENDS)

fclean: 		clean
				$(RM) $(NAME)

re: 
	make fclean
	make all

.PHONY: clean fclean re all

-include $(DEPENDS)
