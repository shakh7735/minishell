#Variables

NAME		=	minishell
SRC_DIR		=	src
SRC_FILES	=	$(wildcard $(SRC_DIR)/*/*.c)
SRCS			= $(SRC_FILES)
OBJS			= $(SRCS:.c=.o)

CC				= cc
CFLAGS			= -Wall -Wextra -Werror $(INCLUDE)
RM				= rm -rf

INCLUDE			= -I $(HOME)/readline/include -I includes
LINKERS			= -L $(HOME)/readline/lib

# Colors

DEF_COLOR	= \033[0;39m
GRAY		= \033[0;90m
RED			= \033[0;91m
GREEN		= \033[0;92m
YELLOW		= \033[0;93m
BLUE		= \033[0;94m
MAGENTA		= \033[0;95m
CYAN		= \033[0;96m
WHITE		= \033[0;97m

all:		$(NAME)

.c.o:
			@$(CC) $(CFLAGS)  -o $@ -c $<

$(NAME):	$(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) -lreadline $(LINKERS) -o $(NAME)
			@echo "$(GREEN)$(NAME) compiled!$(DEF_COLOR)"

clean:
			@$(RM) $(OBJS)
			@echo "$(YELLOW)Cleaned!$(DEF_COLOR)"

fclean: clean
			@$(RM) $(NAME)
			@echo "$(YELLOW)$(NAME) cleaned!$(DEF_COLOR)"

re: fclean all

bonus: all

.PHONY:		all clean fclean re bonus
