# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/02 14:44:14 by ekaik-ne          #+#    #+#              #
#    Updated: 2023/11/03 08:26:01 by ekaik-ne         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
LIBFT = libft/libft.a

CC = gcc
CFLAGS = -g3 -Wall -Wextra

SRC = checker.c images.c init.c layout.c main.c map.c move.c player.c render.c utils.c vector.c texture.c errors.c minimap.c
OBJSDIR = obj
OBJS = $(addprefix $(OBJSDIR)/, $(SRC:%.c=%.o))

.PHONY = all clean fclean re

all: $(NAME)

${NAME}: $(OBJSDIR) $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -I /usr/X11/include -g -L /usr/X11/lib -l mlx -framework OpenGL -framework Appkit $(LIBFT) -o $@

${OBJS}: | $(LIBFT)

${LIBFT}:
	$(MAKE) bonus -C libft/

$(OBJSDIR):
		mkdir -p $@

$(OBJSDIR)/%.o: src/%.c src/cub3D.h
		$(CC) $(CFLAGS) -Imlx -c $< -o $@

clean:
	rm -rf $(OBJSDIR)

fclean: clean
	make fclean -C libft/
	rm -f $(NAME)

re: fclean all