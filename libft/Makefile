# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/12 23:13:40 by ekaik-ne          #+#    #+#              #
#    Updated: 2023/10/05 17:26:47 by ekaik-ne         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS  = -Wall -Werror -Wextra

NAME = libft.a
SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c \
ft_memset.c ft_putchar.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c \
ft_split.c  ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_unsigned_itoa.c \
ft_strlen_mod.c ft_strjoin_mod.c get_next_line.c ft_free_split.c
OBJ = ${SRCS:.c=.o}
SRCS_BONUS =  ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
ft_isdigit.c ft_isprint.c ft_itoa.c ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdel.c \
ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c \
ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar.c ft_putchar_fd.c \
ft_putendl_fd.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c \
ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c \
ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_unsigned_itoa.c \
ft_strlen_mod.c ft_strjoin_mod.c get_next_line.c ft_free_split.c
OBJ_BONUS = ${SRCS_BONUS:.c=.o}

.PHONY = all clean fclean re bonus

all: ${NAME}

${NAME}: $(OBJ)
	@ar -rc ${NAME} $^
	make -C Ft_Printf/
	ar -rs ${NAME} Ft_Printf/*.o

bonus: $(OBJ_BONUS)
	ar -rc ${NAME} $^
	make -C Ft_Printf/
	ar -rs ${NAME} Ft_Printf/*.o

%.o: %.c
	$(CC) $(CFLAGS) -c $^

clean:
	@make fclean -C Ft_Printf
	@rm -f *.o

fclean: clean
	@rm -f ${NAME}

re: fclean all