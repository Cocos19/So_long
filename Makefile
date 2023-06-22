# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/29 10:29:07 by mprofett          #+#    #+#              #
#    Updated: 2023/02/10 09:40:57 by mprofett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= so_long

SRC			= so_long.c so_long_utils.c so_long_map.c so_long_hooks.c

SRC_BONUS	= so_long_bonus.c so_long_utils_bonus.c so_long_map_bonus.c \
			so_long_hooks_bonus.c so_long_images_bonus.c \
			so_long_free_and_exit_bonus.c

OBJ			= ${SRC:.c=.o}

OBJ_BONUS	= ${SRC_BONUS:.c=.o}

LIBFT		= libft.a

LIBFT_PATH	= libft

MLX			= libmlx.a

MLX_PATH	= mlx

CC			= gcc

RM			= rm -f

C_FLAGS	= -Wall -Wextra -Werror

MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit

%.o: %.c
	$(CC) $(C_FLAGS) -c $< -o $@

all: ${NAME}

${NAME}: ${OBJ} ${LIBFT} ${MLX}
	${CC} ${OBJ} -o  ${NAME} ${LIBFT} ${MLX_FLAGS} ${MLX}

${LIBFT}:
	${MAKE} bonus -C ${LIBFT_PATH}
	mv ${LIBFT_PATH}/${LIBFT} .

${MLX}:
	${MAKE} -C ${MLX_PATH}
	mv ${MLX_PATH}/${MLX} .

bonus: ${OBJ_BONUS} ${LIBFT} ${MLX}
	${CC} ${OBJ_BONUS} -o  ${NAME} ${LIBFT} ${MLX_FLAGS} ${MLX}

clean:
	${MAKE} clean -C ${LIBFT_PATH}
	${MAKE} clean -C ${MLX_PATH}
	${RM} ${OBJ} ${OBJ_BONUS}

fclean: clean
	${RM} ${NAME} ${LIBFT} ${MLX}

re:	fclean all

.PHONY:	all bonus clean fclean re
