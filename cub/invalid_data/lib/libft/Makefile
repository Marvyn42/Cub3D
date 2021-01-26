SRC = ft_atoi.c \
  ft_bzero.c \
  ft_calloc.c \
  ft_isalnum.c \
  ft_isalpha.c \
  ft_isascii.c \
  ft_isdigit.c \
  ft_isprint.c \
  ft_itoa.c \
  ft_memccpy.c \
  ft_memchr.c \
  ft_memcmp.c \
  ft_memcpy.c \
  ft_memmove.c \
  ft_memset.c \
  ft_putchar_fd.c \
  ft_putendl_fd.c \
  ft_putnbr_fd.c \
  ft_putstr_fd.c \
  ft_split.c \
  ft_strchr.c \
  ft_strdup.c \
  ft_strjoin.c \
  ft_strlcpy.c \
  ft_strlcat.c \
  ft_strlen.c \
  ft_strmapi.c \
  ft_strncmp.c \
  ft_strnstr.c \
  ft_strrchr.c \
  ft_strtrim.c \
  ft_substr.c \
  ft_tolower.c \
  ft_toupper.c \
  get_next_line.c \
  ft_get_whitespaces.c \
  ft_split_charset.c \
  ft_free.c

BONUS = ft_lstnew.c \
	ft_lstadd_front.c \
	ft_lstsize.c \
	ft_lstlast.c \
	ft_lstadd_back.c \
	ft_lstdelone.c \
	ft_lstclear.c \
	ft_lstiter.c \
	ft_lstmap.c \
  ft_split_charset.c

HEADERS		= libft.h \
		  get_next_line.h

OBJS		= $(SRC:.c=.o)

BNS		= $(BONUS:.c=.o)

NAME		= libft.a

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

RM			= rm -f

all:		$(NAME)

.c.o:
			$(CC) $(CFLAGS) -I . -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
			ar rcs $(NAME) $(OBJS)

bonus:		$(BNS)
			ar rcs $(NAME) $(BNS)

clean:
			$(RM) $(OBJS) $(BNS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
