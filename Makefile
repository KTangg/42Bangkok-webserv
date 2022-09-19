# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/14 23:19:02 by spoolpra          #+#    #+#              #
#    Updated: 2022/09/20 00:23:45 by spoolpra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98
RM = rm -rf

SRC_DIR = srcs/
OBJ_DIR = objs/

NAME = webserv
SRCS = main.cpp worker/Worker.cpp
INCS = -Iincludes/
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

