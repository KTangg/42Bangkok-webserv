# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/14 23:19:02 by spoolpra          #+#    #+#              #
#    Updated: 2023/03/08 15:39:37 by spoolpra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98
RM = rm -rf

SRC_DIR = srcs/
OBJ_DIR = objs/

NAME = webserv
SRCS =	main.cpp \
		component/Header.cpp component/Route.cpp \
		component/Request.cpp component/Response.cpp \
		utils/utils.cpp utils/HttpException.cpp \
		config/MasterConfig.cpp config/ServerConfig.cpp \

INCS = -I includes/
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(addprefix $(OBJ_DIR), $(OBJS))
	$(CC) $(CFLAGS) $^ $(INCS) -o $@

$(OBJ_DIR)%.o:$(SRC_DIR)%.cpp
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(dir $(basename $@))
	$(CC) $(CFLAGS) -c $< $(INCS) -o $@

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

fclean-client:
	$(RM) client

client:
	$(CC) client.cpp -o client

re-c: fclean-client client
