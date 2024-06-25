# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/07 19:24:47 by lumarque          #+#    #+#              #
#    Updated: 2024/06/25 00:54:19 by lumarque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
CC = cc
RM = rm -f
FLAGS = -Wall -Wextra -Werror
MAKE = make -C
LIBFT_PATH = libft
LFLAGS = -L ${LIBFT_PATH} -lft -lreadline
DN = > /dev/null


SRC =	src/minishell.c \
		src/builtins/builtins_basic.c \ 
		src/builtins/builtins_complex.c \ 
		src/builtins/builtins_export_list.c \ 
		src/builtins/builtins_export_tmp.c \ 
		src/builtins/builtins_utils.c



# ------------------------------ Colors ------------------------------

BOLD_PURPLE	=	\033[1;35m
BOLD_CYAN	=	\033[1;36m
BOLD_GREEN	=	\033[1;32m
BOLD_YELLOW	=	\033[1;33m
NO_COLOR	=	\033[0m


# ------------------------------ Message ------------------------------

COMP_START	=	echo "\n $(BOLD_YELLOW)Make: $(NO_COLOR)Starting the compilation...\n"

READY		=	echo "\n $(BOLD_GREEN)Ready$(NO_COLOR) : The program $(BOLD_CYAN) minishell $(NO_COLOR)has been compiled!\n"

CLEANED		=	echo "\n $(BOLD_PURPLE)Clean: $(NO_COLOR)Removed all the \".o\" files \n"

FCLEANED	=	echo "\n $(BOLD_PURPLE)Fclean: $(NO_COLOR)Removed the executables \n"


.c.o:
	@${CC} ${FLAGS} -c $< -o ${<:.c=.o}

OBJ = ${SRC:.c=.o}

${NAME}: ${OBJ}
		@$(COMP_START)
		@${MAKE} ${LIBFT_PATH} $(DN)
		@echo "\n $(BOLD_GREEN)Libft has been compiled!\n" 
		@${CC} ${OBJ} ${LFLAGS} -o ${NAME}
		@$(READY) 

all: ${NAME}

clean:
	@${MAKE} ${LIBFT_PATH} clean $(DN)
	@${RM} ${OBJ}
	@$(CLEANED)

fclean: clean
	@${MAKE} ${LIBFT_PATH} fclean $(DN)
	@${RM} ${NAME}
	@$(FCLEANED)

re: fclean all

.PHONY: all clean fclean re