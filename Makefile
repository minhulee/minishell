# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jewlee <jewlee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/16 23:57:57 by jewlee            #+#    #+#              #
#    Updated: 2024/07/02 14:24:12 by jewlee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
LDFLAGS = -lreadline
RM = rm -f
MAKE_CUR = make -C
LIBFT_DIR = ./libft
LIBFT = ./libft/libft.a
SRCS = ./srcs/main.c \
	./srcs/0_tokenizing/tokenizer.c \
	./srcs/0_tokenizing/tokenizer_utils.c \
	./srcs/0_tokenizing/tokenizer_strtok.c \
	./srcs/0_tokenizing/tokenizer_append.c \
	./srcs/0_tokenizing/tokenizer_lst.c \
	./srcs/0_tokenizing/tokenizer_valid.c \
	./srcs/0_tokenizing/tokenizer_classify.c \
	./srcs/1_parsing/parser.c \
	./srcs/1_parsing/parser_init.c \
	./srcs/1_parsing/parser_lst.c \
	./srcs/1_parsing/parser_f_lst.c \
	./srcs/1_parsing/parser_utils.c \
	./srcs/1_parsing/parser_valid.c \
	./srcs/1_parsing/parser_valid_utils.c \
	./srcs/2_executing/executor.c \
	./srcs/2_executing/executor_path.c \
	./srcs/2_executing/executor_run.c \

OBJS = $(SRCS:.c=.o)
INCLUDES = -L./libft -lft -I./includes

all : $(NAME)

$(NAME) : make_mandatory

make_mandatory : $(OBJS)
	$(MAKE_CUR) $(LIBFT_DIR) bonus
	$(CC) $(LDFLAGS) $(OBJS) $(INCLUDES) -o $(NAME)
	@ touch make_mandatory

debug :
	cc -g -lreadline $(SRCS) ./libft/*.c

dclean :
	rm -rf ./a.out ./a.out.dSYM

%.o : %.c
	$(CC) -c $< -o $@

clean :
	$(MAKE_CUR) $(LIBFT_DIR) clean
	$(RM) $(OBJS)
	@ $(RM) make_mandatory

fclean : clean
	$(MAKE_CUR) $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
