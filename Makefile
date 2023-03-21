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

CF			=	-g -fsanitize=address -Wall -Wextra -Werror

CFLAGS		=	$(if $(filter bonus, $(MAKECMDGOALS)), $(CF) -D BONUS, $(CF))

LFLAGS		=	-L./libft -lft -L./printf -lftprintf

IFLAGS		=	-I./include -I./libft -I./printf/include

MGOALS		=	$(filter-out bonus, $(MAKECMDGOALS))

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
		@$(MAKE) $(MGOALS) -C libft

printf:
		@$(MAKE) $(MGOALS) -C printf

bonus:		libft printf $(NAME)

clean:		printf libft
				@echo "Cleaning Build..."
				@$(RM) $(BUILD)
				@echo "Done."

fclean:		clean
				@echo "Cleaning Everyting..."
				@$(RM) $(NAME)
				@echo "Done."

re:			fclean all

.PHONY:		all clean fclean re libft printf bonus
