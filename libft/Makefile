# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/16 14:47:25 by lumarque          #+#    #+#              #
#    Updated: 2024/08/20 19:57:53 by lumarque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
INCLUDE = libft.h \
			ft_printf.h \
			./42_get_next_line/get_next_line_bonus.h
CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

SRC = ft_atoi.c ft_strlen.c ft_bzero.c ft_memset.c ft_calloc.c ft_isalnum.c \
		ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c \
		ft_memcmp.c ft_split.c ft_putchar_fd.c ft_putstr_fd.c ft_memcpy.c \
		ft_memmove.c ft_putendl_fd.c ft_strchr.c ft_putnbr_fd.c \
		ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strncmp.c \
		ft_strnstr.c ft_strrchr.c ft_substr.c ft_tolower.c ft_toupper.c \
		ft_strmapi.c ft_striteri.c ft_itoa.c ft_strtrim.c ft_free_array.c\
		ft_printf.c ft_print_alpha.c ft_putnbase.c ft_strclen.c	\
		./42_get_next_line/get_next_line_bonus.c \
		./42_get_next_line/get_next_line_utils_bonus.c \
		ft_lstsize.c ft_lstlast.c ft_lstadd_front.c ft_lstadd_back.c \
		ft_lstnew.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
		ft_strcmp.c ft_strjoin_free_s1.c ft_realloc.c \
		
OBJS = ${SRC:.c=.o}

${NAME}: ${OBJS}
	@ar -rcs ${NAME} ${OBJS} ${INCLUDE}

all: ${NAME}

clean: 
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME}

tclean: clean
	@${RM} teste 

re: fclean all

teste: ${NAME}
	@ ${CC} ${CFLAGS} ${INCLUDE} main.c ${NAME} -o teste

.PHONY: all clean fclean re
