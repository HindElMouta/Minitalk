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

#définir le compilateur
CC = cc

#noms des exécutables produits.
CLIENT = client
SERVER = server

#options de compilation
CFLAGS = -Wall -Wextra -Werror

#Règle par défaut
all: $(CLIENT) $(SERVER)

#Compilation des exécutables
$(CLIENT) : client.c 
		$(CC) $(CFLAGS) client.c utils.c -o client
		
$(SERVER) : server.c
		$(CC) $(CFLAGS) server.c utils.c -o server

#Nettoyage
clean:	
		rm -f  $(CLIENT) $(SERVER)

fclean:
	rm -rf $(CLIENT) $(SERVER)

#supprime les binaires.
re: fclean all

#recompilation propre.
.PHONY: all clean fclean re