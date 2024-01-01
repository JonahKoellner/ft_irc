# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mreidenb <mreidenb@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/14 20:49:14 by mreidenb          #+#    #+#              #
#    Updated: 2024/01/01 22:54:15 by mreidenb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = irc
OBJS = $(addprefix .obj/, $(SRC_FILES:.cpp=.o)) .obj/main.o
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -I include -fsanitize=address

SRC_FILES = Server.cpp User.cpp Chat.cpp Executer.cpp Commander.cpp Commands.cpp Commands_Channel.cpp ClientHandler.cpp Database.cpp
SRCS = $(addprefix src/, $(SRC_FILES)) main.cpp

INCLUDE_FILES = Server.hpp User.hpp Chat.hpp Executer.hpp Commander.hpp ClientHandler.hpp Database.hpp Bot.hpp
INCLUDES = $(addprefix include/, $(INCLUDE_FILES))

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

.obj/%.o: src/%.cpp
	mkdir -p .obj
	$(CXX) $(CXXFLAGS) -c $< -o $@
.obj/main.o: main.cpp
	mkdir -p .obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
