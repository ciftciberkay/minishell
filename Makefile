NAME = minishell

SRCS = main.c execution/execute.c  \
	execution/shell_utils.c execution/set_execute.c execution/create_menv.c builtins/ft_echo.c builtins/ft_cd.c builtins/ft_cd_uts.c builtins/ft_env.c \
	builtins/ft_unset.c builtins/ft_pwd.c builtins/ft_export.c builtins/ft_export_uts.c builtins/ft_exit.c  parsing/parser.c parsing/pipe_locs_split_utils.c parsing/parser_utils.c parsing/parser_free.c \
	parsing/substr_utils.c parsing/quoted_utils.c parsing/dollar_utils.c parsing/dollar_parse.c parsing/parser_command.c parsing/command_utils.c parsing/parser_redirect.c parsing/extract_rdr.c parsing/redirect_list.c parsing/redirect_utils.c execution/signals.c execution/execute_uts.c execution/free_ex.c parsing/error_mssg.c parsing/little_utils.c execution/handle_redirects.c execution/processes.c execution/builtin_ex.c execution/set_heredocs.c execution/error_msg.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -I /usr/include/readline -I /usr/local/include/readline
LDFLAGS = -lreadline
RM = rm -f

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(OBJS) libft/libft.a $(LDFLAGS) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@


all: $(NAME) 
	

clean:
	make clean -C libft
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
