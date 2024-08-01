# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/16 23:57:57 by jewlee            #+#    #+#              #
#    Updated: 2024/08/01 15:24:02 by jewlee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= 		minishell
CC 				= 		cc
CFLAGS 			= 		-Wall -Werror -Wextra

RDFLAGS 		= 		-lreadline
# for MacBook
MAC_RDPATH 		= 		-I /opt/homebrew/opt/readline/include
MAC_RDFLAGS 	=		$(RDPATH) -L/opt/homebrew/opt/readline/lib
INCLUDES 		=		-L./libft -lft -I./includes

SRCS			=		./srcs/minishell.c						\
						./srcs/0_init/envp.c 					\
						./srcs/0_init/info.c 					\
						./srcs/0_init/signal.c 					\
						./srcs/1_tokenizing/token.c				\
						./srcs/1_tokenizing/tokenizer.c			\
						./srcs/1_tokenizing/valid.c				\
						./srcs/1_tokenizing/env/env.c			\
						./srcs/1_tokenizing/env/utils.c			\
						./srcs/1_tokenizing/method.c			\
						./srcs/1_tokenizing/utils.c				\
						./srcs/2_parsing/cmd.c					\
						./srcs/2_parsing/file.c					\
						./srcs/2_parsing/parser.c				\
						./srcs/2_parsing/valid.c				\
						./srcs/2_parsing/init/init.c			\
						./srcs/2_parsing/init/utils.c			\
						./srcs/3_executing/heredoc.c			\
						./srcs/3_executing/executor.c			\
						./srcs/3_executing/path.c				\
						./srcs/3_executing/run.c				\
						./srcs/3_executing/set_fd.c				\
						./srcs/3_executing/set_redirect.c		\
						./srcs/3_executing/valid.c				\
						./srcs/3_executing/clear.c				\
						./srcs/4_builtins/builtins.c			\
						./srcs/4_builtins/pwd.c					\
						./srcs/4_builtins/env.c					\
						./srcs/4_builtins/cd.c					\
						./srcs/4_builtins/exit.c				\
						./srcs/4_builtins/echo.c				\
						./srcs/4_builtins/unset.c				\
						./srcs/4_builtins/export/export.c		\
						./srcs/4_builtins/export/utils.c		\
						./srcs/5_exit/exit.c					\


OBJ				=		$(SRCS:.c=.o)

LIBFT_DIR		=		./libft
LIBFT_ARC		=		./libft/libft.a

### COLOR CODE ###
NONE='\033[0m'
GREEN='\033[32m'
YELLOW='\033[33m'
GRAY='\033[2;37m'
CURSIVE='\033[3m'
PURPLE='\033[35m'
BLUE='\033[34m'
DELETELINE='\033[K;
###################

all : $(NAME)
	@make clean

$(NAME) : $(OBJ)
	@make -C $(LIBFT_DIR) bonus
	@echo $(CURSIVE)$(YELLOW) "		- Making $(NAME) -" $(NONE)
	@$(CC) $(CFLAGS) $(RDFLAGS) $^ -o $@ $(LIBFT_ARC)
#	@$(CC) $(CFLAGS) $(MAC_RDFLAGS) $^ -o $@ $(INCLUDES) $(RDFLAGS)
	@echo $(CURSIVE)$(YELLOW) "		- Compiling $(NAME) -" $(NONE)
	@echo $(GREEN) "		- Complete -"$(NONE)

%.o : %.c
	@echo $(CURSIVE)$(YELLOW) "		- Making object files -" $(NONE)
	@$(CC) $(CFLAGS) -c $< -o $@
#	@$(CC) $(CFLAGS) -c $< -o $@ $(MAC_RDPATH)

debug :
	cc -g $(RDFLAGS) $(SRCS) ./libft/*.c

dclean :
	@rm -rf ./a.out ./a.out.dSYM

clean :
	@make -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ)
	@echo $(CURSIVE)$(BLUE) "		- clean OBJ files -" $(NONE)

fclean : clean
	@make -C $(LIBFT_DIR) fclean
	@rm -rf $(NAME)
	@echo $(CURSIVE)$(PURPLE)"		- clean $(NAME) file -"$(NONE)

re  :
	@make fclean
	@make all

.PHONY: all make clean fclean re
