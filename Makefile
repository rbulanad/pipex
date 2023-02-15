# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/10 16:58:42 by rbulanad          #+#    #+#              #
#    Updated: 2023/02/10 10:32:39 by rbulanad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex
NAME_B		= pipexbonus
SOURCES		= pipex.c \
			  pipex_utils.c \
			  pipex_utils2.c \
			  ft_split.c \
			  ft_strjoin.c
SOURCES_B	= ./bonuspart/ft_split_bonus.c \
			  ./bonuspart/ft_strjoin_bonus.c \
			  ./bonuspart/pipex_bonus.c \
			  ./bonuspart/pipex_utils_bonus.c
OBJECTS		= ${SOURCES:.c=.o}
OBJECTS_B	= ${SOURCES_B:.c=.o}
RM		= rm -f
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJECTS}
	${CC} ${CFLAGS} ${OBJECTS} -o ${NAME}
${NAME_B}: ${OBJECTS_B}
	${CC} ${CFLAGS} ${OBJECTS_B} -o ${NAME}

all: ${NAME}

bonus: ${NAME_B}

clean:
	${RM} ${OBJECTS}
	${RM} ${OBJECTS_B}

fclean: clean
	${RM} ${NAME}
	${RM} ${NAME_B}

re: fclean all

.PHONY: all clean fclean re
