# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/18 09:45:34 by zouazrou          #+#    #+#              #
#    Updated: 2025/02/06 09:46:53 by zouazrou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

# EXE
CLIENT = client
SERVER = server

NAME = $(CLIENT) $(SERVER)

# SRC
CCLIENT = client.c utils.c
CSERVER = server.c utils.c

# OBJ
OCLIENT = $(CCLIENT:.c=.o)
OSERVER = $(CSERVER:.c=.o)

# BONUS

# EXE BONUS
B_CLIENT = client_bonus
B_SERVER = server_bonus

# SRC BONUS
BC_CLIENT = client_bonus.c utils_bonus.c
BC_SERVER = server_bonus.c utils_bonus.c

# OBJ BONUS
BO_CLIENT = $(BC_CLIENT:.c=.o)
BO_SERVER = $(BC_SERVER:.c=.o)

# -------------------------------------------------------------------

all : $(NAME)

$(CLIENT) : $(OCLIENT)
	$(CC) $(FLAGS) $^ -o $@

$(SERVER) : $(OSERVER)
	$(CC) $(FLAGS) $^ -o $@

# -------------------------------------------------------------------

bonus : $(B_CLIENT) $(B_SERVER)

$(B_CLIENT) : $(BO_CLIENT)
	$(CC) $(FLAGS) $(BO_CLIENT) -o $(B_CLIENT)

$(B_SERVER) : $(BO_SERVER)
	$(CC) $(FLAGS) $(BO_SERVER) -o $(B_SERVER)

# --------------------------------------------------------------------
clean :
	rm -f $(OCLIENT) $(OSERVER) $(BO_CLIENT) $(BO_SERVER)

fclean : clean
	rm -f $(CLIENT) $(SERVER) $(B_CLIENT) $(B_SERVER)

re : fclean all

.PHONY : all clean fclean re bonus
