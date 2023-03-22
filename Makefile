NAME		=	pipex

INCLUDE		=	./include

BUILD		=	./build

SRC			=	./src

SRC_B		=	./src_b

DEP			=	$(wildcard include/*.h) Makefile

SCS			=	main.c pipes.c utils_1.c utils_2.c \
				utils.c

SCS_B		=	here_doc_bonus.c

SRCS		=	$(patsubst %.c, $(SRC)/%.c, $(SCS))

SRCS_B		=	$(patsubst %.c, $(SRC)/%.c, $(SCS_B))

OBJS		=	$(patsubst $(SRC)/%.c, $(BUILD)/%.o, $(SRCS))

OBJS_B		=	$(patsubst $(SRC)/%.c, $(BUILD)/%.o, $(SRCS_B))

TO_BUILD	=	$(if $(filter bonus, $(MAKECMDGOALS)), $(OBJS) $(OBJS_B), $(OBJS))

CC 			= 	cc

RM			=	rm -rf

CF			=	-g -fsanitize=address -Wall -Wextra -Werror

CFLAGS		=	$(if $(filter bonus, $(MAKECMDGOALS)), $(CF) -D BONUS, $(CF))

LFLAGS		=	-L./libft -lft -L./printf -lftprintf

IFLAGS		=	-I./include -I./libft -I./printf/include

MGOALS		=	$(filter-out bonus, $(MAKECMDGOALS))

$(BUILD)/%.o: $(SRC)/%.c $(DEP)
				$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

all:		libft printf $(NAME)

$(BUILD):
				@mkdir $(BUILD)

$(NAME):	$(BUILD) $(TO_BUILD)
				@echo	"Building ..."
				@echo	$(TO_BUILD)
				@$(CC) $(CFLAGS) $(TO_BUILD) $(IFLAGS) $(LFLAGS) -o $(NAME)
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
