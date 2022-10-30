# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/17 11:02:42 by chenlee           #+#    #+#              #
#    Updated: 2022/10/30 15:40:36 by chenlee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT		= libft/libft.a

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

all:	client server

client:	${LIBFT} client.c
		@${CC} ${CFLAGS} $@.c $< -o $@
		@echo "Compiling: client.c"

server:	${LIBFT} server.c
		@${CC} ${CFLAGS} $@.c $< -o $@
		@echo "Compiling: server.c"
		@echo "  -----------------"
		@echo " |  Minitalk Done! |"
		@echo "  -----------------"

${LIBFT}:
		@make -C libft

clean:
		@rm -rf libft/objects
		@echo "Remove: libft/objects"
		
fclean:	clean
		@rm -rf libft/libft.a
		@rm -rf client server
		@echo "Remove: libft/libft.a"
		@echo "Remove: client"
		@echo "Remove: server"

re:		fclean all
