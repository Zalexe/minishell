# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/19 15:31:19 by cmarrued          #+#    #+#              #
#    Updated: 2025/06/19 17:21:25 by intherna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
CC		= cc

CFLAGS	= -Wall -Wextra -Werror -c

NAME	= libft.a

HEADER	= libft.h

SRCS	= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_printf_handle.c ft_printf_utils.c ft_printf_utils2.c ft_printf.c get_next_line.c get_next_line_utils.c ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c ft_lstwrapper.c

SRCB	= ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c

OBJS	= ${SRCS:.c=.o}

OBJB	= ${SRCB:.c=.o}

RM		= rm -f

AR		= ar -rcs

all:		${NAME}

%.o: %.c		$(HEADER) $(SRCS) Makefile 
			${CC} ${CFLAGS} $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			${AR} ${NAME} ${OBJS}
			
bonus:		${OBJS} ${OBJB}
			${AR} ${NAME} ${OBJB}
clean:
			${RM} ${OBJS} ${OBJB}

fclean:		clean
			${RM} ${NAME}

re:			fclean all bonus

.PHONY:		all clean fclean re bonus
