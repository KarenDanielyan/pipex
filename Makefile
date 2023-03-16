NAME		=	pipex

INCLUDE		=	./include

BUILD		=	./build

SRC			=	./src

SRC_B		=	./src_b

DEP			=	$(wildcard include/*.h) Makefile

SOURCES		=	$(wildcard $(SRC)/*.c)

OBJS		=	$(patsubst $(SRC)/%.c, $(BUILD)/%.o, $(SOURCES))

CC 			= 	cc

RM			=	rm -rf

CFLAGS		=	-g3 #-fsanitize=address #-Wall -Wextra -Werror

LFLAGS		=	-L./libft -lft -L./printf -lftprintf

IFLAGS		=	-I./include -I./libft -I./printf/include

$(BUILD)/%.o: $(SRC)/%.c $(DEP)
				@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

all:		libft printf $(NAME)

$(BUILD):
				@mkdir $(BUILD)

$(NAME):	$(BUILD) $(OBJS)
				@echo	"Building ..."
				@$(CC) $(CFLAGS) $(OBJS) $(IFLAGS) $(LFLAGS) -o $(NAME)
				@echo	"Build Successfull."

libft:
		@$(MAKE) $(MAKECMDGOALS) -C libft

printf:
		@$(MAKE) $(MAKECMDGOALS) -C printf

clean:		printf libft
				@echo "Cleaning Build..."
				@$(RM) $(BUILD)
				@echo "Done."

fclean:		clean
				@echo "Cleaning Everyting..."
				@$(RM) $(NAME)
				@echo "Done."

re:			fclean all

bonus:		$(BONUS)

.PHONY:		all bonus clean fclean re libft printf
