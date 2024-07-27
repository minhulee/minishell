NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g 
AR = ar
ARFLAGS = rcs
RM = rm -f
SRCS = \
./ft_isalpha.c \
./ft_isdigit.c \
./ft_isalnum.c \
./ft_isascii.c \
./ft_isprint.c \
./ft_strlen.c \
./ft_memset.c \
./ft_bzero.c \
./ft_memcpy.c \
./ft_memmove.c \
./ft_strlcpy.c \
./ft_strlcat.c \
./ft_toupper.c \
./ft_tolower.c \
./ft_strchr.c \
./ft_strrchr.c \
./ft_strncmp.c \
./ft_strncpy.c \
./ft_memchr.c \
./ft_memcmp.c \
./ft_strnstr.c \
./ft_atoi.c \
./ft_calloc.c \
./ft_strdup.c \
./ft_substr.c \
./ft_strjoin.c \
./ft_strtrim.c \
./ft_split.c \
./ft_itoa.c \
./ft_strmapi.c \
./ft_striteri.c \
./ft_putchar_fd.c \
./ft_putstr_fd.c \
./ft_putendl_fd.c \
./ft_putnbr_fd.c \
./get_next_line.c \
./get_next_line_utils.c \
./ft_fprintf.c \
./ft_fprintf_utils1.c \
./ft_fprintf_utils2.c
OBJS = $(SRCS:.c=.o)
SRCS_BONUS =  \
./ft_lstnew_bonus.c \
./ft_lstadd_front_bonus.c \
./ft_lstsize_bonus.c \
./ft_lstlast_bonus.c \
./ft_lstadd_back_bonus.c \
./ft_lstdelone_bonus.c \
./ft_lstclear_bonus.c \
./ft_lstiter_bonus.c \
./ft_lstmap_bonus.c
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

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

$(NAME) : make_mandatory

bonus : make_bonus

make_mandatory : $(OBJS)
	@ echo $(CURSIVE)$(YELLOW) "		- Making $(NAME) -" $(NONE)
	@ $(AR) $(ARFLAGS) $(NAME) $^
	@ touch $@
	@ echo $(CURSIVE)$(YELLOW) "		- Compiling $(NAME) -" $(NONE)
	@ echo $(GREEN) "		- Complete -"$(NONE)

make_bonus : $(OBJS) $(OBJS_BONUS)
	@ echo $(CURSIVE)$(YELLOW) "		- Making $(NAME) -" $(NONE)
	@ $(AR) $(ARFLAGS) $(NAME) $^
	@ touch $@
	@ echo $(CURSIVE)$(YELLOW) "		- Compiling $(NAME) -" $(NONE)
	@ echo $(GREEN) "		- Complete -"$(NONE)

%.o : %.c
	@ echo $(CURSIVE)$(YELLOW) "		- Making object files -" $(NONE)
	@ $(CC) $(CFLAGS) -c $< -o $@
	

clean :
	@ $(RM) $(OBJS) $(OBJS_BONUS)
	@ $(RM) make_mandatory
	@ $(RM) make_bonus
	@ echo $(CURSIVE)$(BLUE) "		- clean OBJ files -" $(NONE)

fclean : clean
	@ $(RM) $(NAME)
	@ echo $(CURSIVE)$(PURPLE)"		- clean $(NAME) file -"$(NONE)

re : fclean all

.PHONY : all bonus clean fclean re
