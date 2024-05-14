# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 09:58:18 by nlewicki          #+#    #+#              #
#    Updated: 2024/05/08 09:03:37 by nlewicki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk
CC = cc
CFLAGS = -Wall -Wextra -Werror

CLIENT = client.c
SERVER = server.c

CLIENT_EXE = client
SERVER_EXE = server

LIBFT = libft/libft.a
PRINTF = ft_printf/libftprintf.a

${NAME}: libft printf $(CLIENT_EXE) $(SERVER_EXE)
	@echo "\033[32mCompilation done\033[0m"
	@sleep 2
	@clear

client: $(CLIENT) $(LIBFT) $(PRINTF)
	@$(CC) $(CFLAGS) $(CLIENT) $(LIBFT) $(PRINTF) -o $(CLIENT_EXE)

server: $(SERVER) $(LIBFT) $(PRINTF)
	@$(CC) $(CFLAGS) $(SERVER) $(LIBFT) $(PRINTF) -o $(SERVER_EXE)

printf:
	@make -C ft_printf

libft:
	@make -C libft

all: $(NAME)

clean:
	rm -f $(CLIENT_EXE) $(SERVER_EXE)
	@make -C libft clean
	@make -C ft_printf clean
	@echo "\033[33mCleaning done - clean\033[0m"

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT) $(PRINTF)
	@echo "\033[31mCleaning done - fclean\033[0m"
	@sleep 2
	@clear

re: fclean all

.PHONY: all clean fclean re libft
