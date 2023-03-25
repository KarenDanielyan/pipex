# Program and it's dependencies

NAME		=	pipex

INCLUDE		=	./include

BUILD		=	./build

SRC			=	./src

SRC_B		=	./src_b

SCS			=	logic.c main.c pipes.c process.c \
				utils.c

SCS_B		=	get_next_line_bonus.c get_next_line_utils_bonus.c \
				here_doc_bonus.c logic_bonus.c main_bonus.c \
				pipes_bonus.c process_bonus.c utils_bonus.c

DEP			=	$(wildcard $(INCLUDE)/*.h) Makefile

SRCS		=	$(patsubst %.c, $(SRC)/%.c, $(SCS))

SRCS_B		=	$(patsubst %.c, $(SRC_B)/%.c, $(SCS_B))

OBJS		=	$(patsubst $(SRC)/%.c, $(BUILD)/%.o, $(SRCS))

OBJS_B		=	$(patsubst $(SRC_B)/%.c, $(BUILD)/%.o, $(SRCS_B))

TO_BUILD	=	$(if $(filter bonus, $(MAKECMDGOALS)), $(OBJS_B), $(OBJS))

# Compilation options

CC 			= 	cc

RM			=	rm -rf

CF			=	-g #-fsanitize=address -Wall -Wextra -Werror

CFLAGS		=	$(if $(filter bonus, $(MAKECMDGOALS)), $(CF) -D BONUS, $(CF))

LFLAGS		=	-L./libft -lft -L./printf -lftprintf

IFLAGS		=	-I./include -I./libft -I./printf/include

MGOALS		=	$(filter-out bonus, $(MAKECMDGOALS))

# Colors

RESET  = \033[0m
RED    = \033[31m
GREEN  = \033[32m
YELLOW = \033[33m
BLUE   = \033[34m


# Recipies

$(BUILD)/%.o:	$(SRC)/%.c $(DEP)
					@echo "${YELLOW}Compiling $<.${RESET}"
					@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(BUILD)/%.o:	$(SRC_B)/%.c $(DEP)
					@echo "${YELLOW}Compiling $<${RESET}"
					@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

all:		wait_msg libft printf $(NAME)

$(BUILD):
				@mkdir $(BUILD)

$(NAME):	$(BUILD) $(TO_BUILD)
				@echo "${GREEN}Building pipex.${RESET}"
				@$(CC) $(CFLAGS) $(TO_BUILD) $(IFLAGS) $(LFLAGS) -o $(NAME)
				@echo "${GREEN}Build Successfull.${RESET}"

libft:
				@$(MAKE) $(MGOALS) -C libft

printf:
				@$(MAKE) $(MGOALS) -C printf

bonus:		wait_msg libft printf $(NAME)

wait_msg:
				@echo "${BLUE}Please wait for pipex to compile.${RESET}"

clean:		printf libft
				@echo "${YELLOW}Cleaning Build...${RESET}"
				@$(RM) $(BUILD)
				@echo "${GREEN}Done.${RESET}"

fclean:		printf libft
				@echo "${YELLOW}Cleaning Everyting...${RESET}"
				@$(RM) $(BUILD)
				@$(RM) $(NAME)
				@echo "${GREEN}Done.${RESET}"

re:			fclean all

.PHONY:		all clean fclean re libft printf bonus wait_msg
