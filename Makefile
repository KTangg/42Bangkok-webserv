# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/14 23:19:02 by spoolpra          #+#    #+#              #
#    Updated: 2024/01/08 14:27:35 by spoolpra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98
RM = rm -rf

SRC_DIR = srcs/
OBJ_DIR = objs/

NAME = webserv
SRCS =	main.cpp \
		config/Config.cpp config/ServerConfig.cpp\
		error/ErrorPage.cpp \
		handling/Request.cpp handling/Header.cpp handling/Response.cpp\
		logger/Logger.cpp \
		parser/Parser.cpp parser/RequestParser.cpp\
		route/Route.cpp route/Cgi.cpp \
		server/Master.cpp server/Worker.cpp server/Server.cpp server/Poller.cpp \
		utils/utils.cpp utils/status_code.cpp \

INCS = -I includes/ -I srcs/
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
	$(CC) srcs/client.cpp -o client

re-c: fclean-client client
