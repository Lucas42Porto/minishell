# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/07 19:24:47 by lumarque          #+#    #+#              #
#    Updated: 2024/06/04 22:54:20 by lumarque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
CC = cc
RM = rm -f
FLAGS = -Wall -Wextra -Werror -g
MAKE = make -C
LIBFT_PATH = libft
LFLAGS = -L ${LIBFT_PATH} -lft -lreadline
DN = > /dev/null

SRC_DIRS = src src/env src/parser src/utils src/executor src/expand src/builtins

SRC =	$(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))


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

OBJ = ${SRC:.c=.o}

.c.o:
	@${CC} ${FLAGS} -c $< -o ${<:.c=.o}


${NAME}: ${OBJ}
		@$(COMP_START)
		@${MAKE} ${LIBFT_PATH} $(DN)
		@echo "\n $(BOLD_GREEN)Libft has been compiled!\n" 
		@${CC} ${OBJ} ${LFLAGS} -o ${NAME}
		@$(READY) 

all: ${NAME}

clean:
	@${MAKE} ${LIBFT_PATH} clean $(DN)
	@${RM} ${OBJ} output.log readline.supp
	@$(CLEANED)

fclean: clean
	@${MAKE} ${LIBFT_PATH} fclean $(DN)
	@${RM} ${NAME}
	@$(FCLEANED)

re: fclean all

test1: ${NAME}
	@bash ./test/test1.sh

test2: ${NAME}
	@bash ./test/test2.sh

leaks: readline.supp
	valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --log-file=output.log ./minishell

readline.supp:
	@echo "{" > readline.supp
	@echo "    leak readline" >> readline.supp
	@echo "    Memcheck:Leak" >> readline.supp
	@echo "    ..." >> readline.supp
	@echo "    fun:readline" >> readline.supp
	@echo "}" >> readline.supp
	@echo "{" >> readline.supp
	@echo "    leak add_history" >> readline.supp
	@echo "    Memcheck:Leak" >> readline.supp
	@echo "    ..." >> readline.supp
	@echo "    fun:add_history" >> readline.supp
	@echo "}" >> readline.supp


.PHONY: all clean fclean re test1 test2 leaks
