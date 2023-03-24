NAME		=	pipex

INCLUDE		=	./include

BUILD		=	./build

SRC			=	./src

SRC_B		=	./src_b

DEP			=	$(wildcard include/*.h) Makefile

SCS			=	logic.c main.c pipes.c process.c \
				utils.c

SCS_B		=	get_next_line_bonus.c get_next_line_utils_bonus.c \
				here_doc_bonus.c logic_bonus.c main_bonus.c \
				pipes_bonus.c process_bonus.c utils_bonus.c

SRCS		=	$(patsubst %.c, $(SRC)/%.c, $(SCS))

SRCS_B		=	$(patsubst %.c, $(SRC_B)/%.c, $(SCS_B))

OBJS		=	$(patsubst $(SRC)/%.c, $(BUILD)/%.o, $(SRCS))

OBJS_B		=	$(patsubst $(SRC_B)/%.c, $(BUILD)/%.o, $(SRCS_B))

TO_BUILD	=	$(if $(filter bonus, $(MAKECMDGOALS)), $(OBJS_B), $(OBJS))

CC 			= 	cc

RM			=	rm -rf

CF			=	-g -fsanitize=address -Wall -Wextra -Werror

CFLAGS		=	$(if $(filter bonus, $(MAKECMDGOALS)), $(CF) -D BONUS, $(CF))

LFLAGS		=	-L./libft -lft -L./printf -lftprintf

IFLAGS		=	-I./include -I./libft -I./printf/include

MGOALS		=	$(filter-out bonus, $(MAKECMDGOALS))

$(BUILD)/%.o:	$(SRC)/%.c $(DEP)
					$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(BUILD)/%.o:	$(SRC_B)/%.c $(DEP)
					$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

all:		libft printf $(NAME)

$(BUILD):
				@mkdir $(BUILD)

$(NAME):	$(BUILD) $(TO_BUILD)
				@echo	"Building ..."
				@echo	$(TO_BUILD)
				$(CC) $(CFLAGS) $(TO_BUILD) $(IFLAGS) $(LFLAGS) -o $(NAME)
				@echo	"Build Successfull."

libft:
		@$(MAKE) $(MGOALS) -C libft

printf:
		@$(MAKE) $(MGOALS) -C printf

bonus:		libft printf $(NAME)

mini_clean:
			@$(RM) $(OBJS) $(OBJS_B)

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
