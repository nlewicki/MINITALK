# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 09:58:18 by nlewicki          #+#    #+#              #
#    Updated: 2024/06/27 14:12:11 by nlewicki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk
CC = cc
CFLAGS = -Wall -Wextra -Werror

CLIENT = client.c
SERVER = server.c

CLIENT_EXE = client
SERVER_EXE = server

LIBFT_DIR = libft
PRINTF_DIR = ft_printf

LIBFT = $(LIBFT_DIR)/libft.a
PRINTF = $(PRINTF_DIR)/libftprintf.a

$(NAME): libft printf $(CLIENT_EXE) $(SERVER_EXE)
	@echo "\033[32mCompilation done\033[0m"
	@sleep 2
	@clear

$(CLIENT_EXE): $(CLIENT) $(LIBFT) $(PRINTF)
	@$(CC) $(CFLAGS) $(CLIENT) $(LIBFT) $(PRINTF) -o $(CLIENT_EXE)

$(SERVER_EXE): $(SERVER) $(LIBFT) $(PRINTF)
	@$(CC) $(CFLAGS) $(SERVER) $(LIBFT) $(PRINTF) -o $(SERVER_EXE)

printf:
	@make -C $(PRINTF_DIR)

libft:
	@make -C $(LIBFT_DIR)

all: libft ft_printf $(NAME)

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

.PHONY: all clean fclean re libft ft_printf
