# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/14 23:19:02 by spoolpra          #+#    #+#              #
#    Updated: 2024/03/01 21:01:11 by tratanat         ###   ########.fr        #
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
		logger/Logger.cpp \
		parser/Parser.cpp \
		route/Route.cpp route/Cgi.cpp \
		server/Master.cpp server/Worker.cpp server/Server.cpp server/Poller.cpp \
		http/HttpRequest.cpp http/HttpResponse.cpp \
		utils/status_code.cpp utils/utils.cpp utils/mime_types.cpp \

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
