# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jonahkollner <jonahkollner@student.42.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/08 09:50:40 by jkollner          #+#    #+#              #
#    Updated: 2023/10/08 19:52:53 by jonahkollne      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

name = irc
cc = c++
cflags = -Wall -Werror -Wextra -std=c++98
src = main.cpp server.cpp User.cpp
obj = ${src:.cpp=.o}

all: ${name}

${name}: ${obj}
	${cc} ${cflags} ${obj} -o ${name}

clean:
	rm ${obj}

fclean: clean
	rm ${name}

re:	fclean all

.PHONY: all ${name} clean fclean
