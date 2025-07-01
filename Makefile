NAME = minishell
NAME_BONUS = minishell_bonus

CC = cc
SHFLAGS = -Wall -Wextra -Werror -MMD -O3

INCDIR = include
LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_DIR = src
SRC_BUILTIN_DIR = $(SRC_DIR)/builtin
SRC_ENV_DIR = $(SRC_DIR)/env
SRC_EXECUTOR_DIR = $(SRC_DIR)/executor
SRC_PARSER_DIR = $(SRC_DIR)/parser

SRC_BONUS = $(SRC_DIR)/error_handler.c $(SRC_DIR)/main_bonus.c $(SRC_DIR)/prompt.c $(SRC_DIR)/signal.c $(SRC_DIR)/utils.c $(SRC_DIR)/lst_utils.c $(SRC_DIR)/pid.c \
			$(SRC_BUILTIN_DIR)/builtin.c $(SRC_BUILTIN_DIR)/cd.c $(SRC_BUILTIN_DIR)/echo.c $(SRC_BUILTIN_DIR)/env_builtin.c \
			$(SRC_BUILTIN_DIR)/exit.c $(SRC_BUILTIN_DIR)/export.c $(SRC_BUILTIN_DIR)/pwd.c $(SRC_BUILTIN_DIR)/unset.c \
			$(SRC_ENV_DIR)/env.c $(SRC_ENV_DIR)/env_injector.c $(SRC_ENV_DIR)/env_utils.c \
			$(SRC_EXECUTOR_DIR)/executor.c $(SRC_EXECUTOR_DIR)/heredoc.c $(SRC_EXECUTOR_DIR)/pipe.c $(SRC_EXECUTOR_DIR)/command_path.c $(SRC_EXECUTOR_DIR)/pipe_util.c \
			$(SRC_PARSER_DIR)/parser.c $(SRC_PARSER_DIR)/quotes.c $(SRC_PARSER_DIR)/settings_parser.c $(SRC_PARSER_DIR)/cleanup.c $(SRC_PARSER_DIR)/asterisk_injector_bonus.c \
			$(SRC_PARSER_DIR)/asterisk_utils_bonus.c $(SRC_PARSER_DIR)/asterisk_quote_handler_bonus.c
OBJ_BONUS = $(SRC_BONUS:.c=.o)
DEPS_BONUS = $(SRC_BONUS:.c=.d)

SRC = $(SRC_DIR)/error_handler.c $(SRC_DIR)/main.c $(SRC_DIR)/prompt.c $(SRC_DIR)/signal.c $(SRC_DIR)/utils.c $(SRC_DIR)/lst_utils.c $(SRC_DIR)/pid.c \
	  $(SRC_BUILTIN_DIR)/builtin.c $(SRC_BUILTIN_DIR)/cd.c $(SRC_BUILTIN_DIR)/echo.c $(SRC_BUILTIN_DIR)/env_builtin.c \
	  $(SRC_BUILTIN_DIR)/exit.c $(SRC_BUILTIN_DIR)/export.c $(SRC_BUILTIN_DIR)/pwd.c $(SRC_BUILTIN_DIR)/unset.c \
	  $(SRC_ENV_DIR)/env.c $(SRC_ENV_DIR)/env_injector.c $(SRC_ENV_DIR)/env_utils.c \
	  $(SRC_EXECUTOR_DIR)/executor.c $(SRC_EXECUTOR_DIR)/heredoc.c $(SRC_EXECUTOR_DIR)/pipe.c $(SRC_EXECUTOR_DIR)/command_path.c $(SRC_EXECUTOR_DIR)/pipe_util.c \
	  $(SRC_PARSER_DIR)/parser.c $(SRC_PARSER_DIR)/quotes.c $(SRC_PARSER_DIR)/settings_parser.c $(SRC_PARSER_DIR)/cleanup.c $(SRC_PARSER_DIR)/asterisk_quote_handler_bonus.c
OBJ = $(SRC:.c=.o)
DEPS = $(SRC:.c=.d)

MODE = mandatory

INCLUDES = -I$(INCDIR)/$(MODE) -I$(INCDIR) -I$(LIBFT_DIR)

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c Makefile
	$(CC) $(SHFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(SHFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)

$(NAME_BONUS): $(LIBFT) $(OBJ_BONUS)
	$(CC) $(SHFLAGS) $(OBJ_BONUS) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME_BONUS)

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJ)
	rm -f $(DEPS)
	rm -f $(OBJ_BONUS)
	rm -f $(DEPS_BONUS)

fclean:
	make -C $(LIBFT_DIR) fclean
	rm -f $(OBJ)
	rm -f $(NAME)
	rm -f $(DEPS)
	rm -f $(OBJ_BONUS)
	rm -f $(NAME_BONUS)
	rm -f $(DEPS_BONUS)

re: fclean all

__do_bonus: $(NAME_BONUS)

bonus:
	make MODE="bonus" __do_bonus

debug: fclean
	make SHFLAGS="-Wall -Wextra -Werror -MMD -g -fsanitize=address" bonus

.PHONY: all clean fclean re bonus __do_bonus debug

-include $(DEPS)
-include $(DEPS_BONUS)
