NAME		= minishell

LIB_DIRS	= libft
SRCS_DIRS	= src
OBJS_DIRS   = obj
INCL_DIRS	= includes
SRC			= $(shell find $(SRCS_DIRS) -type f -name "*.c")
OBJS 		= $(SRC:$(SRCS_DIRS)/%.c=$(OBJS_DIRS)/%.o)
INCLUDE		= $(addprefix -I, $(INCL_DIRS))
LIB			= $(shell find $(LIB_DIRS) -type f -name "*.a")

CC			= gcc
FLAGS		= -Wall -Wextra -Werror -g -fsanitize=address
RED			= \033[0;31m
GREEN		= \033[0;32m
ORANGE		= \033[0;33m
BLUE		= \033[1;34m
YELLOW		= \033[1;33m
NC			= \033[0m

all: 		libft $(NAME)

bonus:		libft $(BONUS)

libft:
			@echo "\n$(GREEN)Compiling libft:$(NC)"
			@$(MAKE) -C libft/

.c.o:
			@echo "Creating object: $@"
			@$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

$(OBJS_DIRS)/%.o: $(SRCS_DIRS)/%.c 
		@mkdir -p $(dir $@)
		$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

$(NAME):	$(OBJS)
			@$(CC) -o $(NAME) -lreadline -L .brew/opt/readline/lib -I .brew/opt/readline/include $(FLAGS) $(INCLUDE) $(LIB) $(OBJS)

clean:
			@rm -f -rf $(OBJS_DIRS)
			@$(MAKE) -C libft/ clean && echo "$(GREEN)libft objects removed!$(NC)"

fclean: 	clean
			@rm -f $(OBJS)
			@rm -f $(NAME)
			@rm -f $(BONUS)
			@$(MAKE) -C libft/ fclean

re:			fclean all

.PHONY:		all clean fclean re libft
