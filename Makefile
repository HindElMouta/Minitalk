# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/11 15:05:50 by hinel-mo          #+#    #+#              #
#    Updated: 2025/02/11 15:05:50 by hinel-mo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CFLAGS = -Wall -Werror -Wextra
CC = cc
CLIENT = client
SERVER = server
CFLAGS = -Wall -Wextra -Werror

all: $(CLIENT) $(SERVER)

$(CLIENT) : client.c 
		$(CC) $(CFLAGS) client.c utils.c -o client
		
$(SERVER) : server.c
		$(CC) $(CFLAGS) server.c utils.c -o server

clean:	
		rm -f  $(CLIENT) $(SERVER)

fclean:
	rm -rf $(CLIENT) $(SERVER)

re: fclean all

.PHONY: all clean fclean re