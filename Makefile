#_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_ COLORS _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_
RESET	= \033[0m
BLACK 	= \033[1;30m
RED 	= \033[1;31m
GREEN 	= \033[1;32m
YELLOW 	= \033[1;33m
BLUE	= \033[1;34m
PURPLE 	= \033[1;35m
CYAN 	= \033[1;36m
WHITE 	= \033[1;37m

#_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_ COMMANDS _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_
CC = cc
RM = rm -rf
AR = ar -rcs

#_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_ FLAGS _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_
CFLAGS	= -Wall -Wextra -Werror -g -fsanitize=address
MK		= --no-print-directory
LIBFT	= -L ./libft -lft
GNL		= -L ./get_next_line -lgnl
PRINTF	= -L ./ft_printf -lftprintf

#_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_ FOLDERS _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_
DEPS			= inc 
SRCS			= src
#SRCS_BONUS		= srcs_bonus
LIBFT_PATH		= libft
GNL_PATH		= get_next_line
PRINTF_PATH		= ft_printf
_SUBFOLDERS		= 
VPATH			= $(addprefix $(SRCS)/, $(_SUBFOLDERS))
OBJ_DIR			= objs
#OBJ_DIR_BONUS	= objs_bonus

#_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_ FILES _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_
NAME			= minishell
_FILES			= ast cd echo env exec export_unset fake_global input lexer lists no_leaks \
					main parser scanner testing utils utils2 utils3
OBJS			= $(_FILES:%=%.o)
TARGET			= $(addprefix $(OBJ_DIR)/, $(OBJS))


#_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_ RULES _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_
all: $(NAME)

$(NAME): $(OBJ_DIR) $(TARGET)
	echo "[$(CYAN)Compiling$(RESET)] $(CFLAGS) $(GREEN)libft/*$(RESET)"
	make $(MK) -C $(LIBFT_PATH)
		
	echo "[$(CYAN) Linking $(RESET)] $(GREEN)*$(RESET)"
	$(CC) $(CFLAGS) $(TARGET) -o $(NAME) -I $(DEPS) -lreadline $(LIBFT)
	
	echo "$(GREEN)Done.$(RESET)"
	
$(OBJ_DIR)/%.o : $(SRCS)/%.c 
	echo "[$(CYAN)Compiling$(RESET)] $(CFLAGS) $(GREEN)$<$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@ -I $(DEPS) $(LIBFT)

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)

clean:
	make clean $(MK) -C $(LIBFT_PATH)
	
	echo "[$(RED) Deleted $(RESET)] $(GREEN)$(OBJ_DIR)$(RESET)"
	$(RM) $(OBJ_DIR)

fclean: clean
	make fclean $(MK) -C $(LIBFT_PATH)
	
	echo "[$(RED) Deleted $(RESET)] $(GREEN)$(NAME)$(RESET)"
	$(RM) $(NAME) 

re: fclean all

r: re
	./minishell

.SILENT:

.PHONY: libft all bonus clean fclean re r

