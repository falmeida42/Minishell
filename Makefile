NAME		= minishell

FT_DIR		= libft

SRCS_DIRS	= src
OBJS_DIRS   = obj
INCL_DIRS	= includes $(FT_DIR)

SRC			= $(shell find $(SRCS_DIRS) -type f -name "*.c")
OBJS 		= $(SRC:$(SRCS_DIRS)/%.c=$(OBJS_DIRS)/%.o)

INC_FLAGS	= $(addprefix -I, $(INCL_DIRS))
WARN_FLAGS	= -Wall -Wextra -Werror
DEBUG_FLAGS = -g -fsanitize=address
LIBS_FLAGS	= -L$(FT_DIR) -lft -lreadline 

CFLAGS		= $(WARN_FLAGS) $(INC_FLAGS)
LDFLAGS		= $(WARN_FLAGS) $(LIBS_FLAGS)

CC			= gcc
RM			= rm -f

RED			= \033[0;31m
GREEN		= \033[0;32m
ORANGE		= \033[0;33m
BLUE		= \033[1;34m
YELLOW		= \033[1;33m
NC			= \033[0m

all: 		libft $(NAME)

libft:
			@echo "\n$(GREEN)Compiling libft:$(NC)"
			@$(MAKE) -C libft

.c.o:
			@echo "Creating object: $@"
			@$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

$(OBJS_DIRS)/%.o: $(SRCS_DIRS)/%.c 
		@mkdir -p $(dir $@)
		$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
			@$(CC) $^ -o $(NAME) $(LDFLAGS)

clean:
			@$(RM) -rf $(OBJS_DIRS)
			@$(MAKE) -C libft/ clean && echo "$(GREEN)libft objects removed!$(NC)"

fclean: 	clean
			@rm -f $(OBJS)
			@rm -f $(NAME)
			@$(MAKE) -C libft/ fclean

re:			fclean all

debug:		CFLAGS += $(DEBUG_FLAGS)
debug:		LDFLAGS += $(DEBUG_FLAGS) -lasan 
debug:		re

.PHONY:		all clean fclean re libft
