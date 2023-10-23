# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkollner <jkollner@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/08 09:50:40 by jkollner          #+#    #+#              #
#    Updated: 2023/10/23 12:10:50 by jkollner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

name = irc
cc = c++
cflags = -Wall -Werror -Wextra -std=c++98
src = main.cpp Server.cpp User.cpp Chat.cpp Executer.cpp Commander.cpp ClientHandler.cpp Database.cpp
obj = ${src:.cpp=.o}

all: ${name}

${name}: ${obj}
	${cc} ${cflags} ${obj} -o ${name}

clean:
	rm -f ${obj}

fclean: clean
	rm -f ${name}

re:	fclean all

.PHONY: all ${name} clean fclean
