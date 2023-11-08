NAME	=	minishell

LIBFT_DIR	=	libft/
LIBFT_NAME	=	libft.a
LIBFT		=	$(addprefix $(LIBFT_DIR), $(LIBFT_NAME))

INC            :=    minishell.h
INC_DIR        :=    inc/

HEADERS        := $(addprefix $(INC_DIR), $(INC))

SRC_DIR        :=	src/
SRC            :=	main.c\
					utils/error.c utils/utils.c utils/token_utils.c\
					tokenizer/tokenizer.c

COMPILED = 0
TOTAL_COMPILATION = $(shell ((echo ${SRC}) | wc -w | sed -e 's/^[ \t]*//'))

OBJ_DIR        :=    obj/
OBJ            :=    $(SRC:%.c=$(OBJ_DIR)%.o)

# define standard colors
_END        :=    \x1b[0m
_BOLD       :=    \x1b[1m
_UNDER      :=    \x1b[4m
_REV        :=    \x1b[7m
_GREY       :=    \x1b[30m
_RED        :=    \x1b[31m
_GREEN      :=    \x1b[32m
_YELLOW     :=    \x1b[33m
_BLUE       :=    \x1b[34m
_PURPLE     :=    \x1b[35m
_CYAN       :=    \x1b[36m
_WHITE      :=    \x1b[37m

#Compiler
CC            :=    cc
CC_FLAGS      :=    -Wextra -Werror -Wall


all: $(NAME)

$(NAME): $(OBJ) libft
	$(CC) $(CC_FLAGS) $(OBJ) -L ./libft -lft -lreadline -o $@
	@echo "All compiled"

$(OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS) Makefile
	@mkdir -p $(@D)
	@$(eval COMPILED=$(shell echo $$((${COMPILED}+1))))
	@echo "Compiling in progress ${COMPILED}/${TOTAL_COMPILATION}"
	@$(CC) $(CC_FLAGS) -I $(INC_DIR) -c $< -o $@

libft:
	@make -C libft

clean: cleanlibft
	@rm -rf $(OBJ_DIR)
	@echo "Everything removed"

fclean: fcleanlibft clean
	@rm -rf $(NAME)

cleanlibft:
	@make clean -C ${LIBFT_DIR}

fcleanlibft: cleanlibft
	@make fclean -C ${LIBFT_DIR}

re: fclean all

.PHONY: all clean fclean re libft