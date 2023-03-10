NAME		=	libft.a

DEP			= 	libft.h Makefile

SOURCES		=	$(shell find . -maxdepth 1 -name '*.c')

CC 			= 	cc

OBJS		=	$(SOURCES:.c=.o)

RM			=	rm -f

CFLAGS		=	-g3 -Wall -Wextra -Werror

AR			=	ar rcs

%.o: %.c $(DEP)
				@$(CC) $(CFLAGS) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS)
				@echo "Building Libft..."
				@$(AR) $(NAME) $(OBJS)
				@echo Done.

clean:		
				@$(RM) $(OBJS)

fclean:		clean
				@$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY:		all bonus clean fclean re