NAME = jmakela.filler

V_NAME = visu

CC = gcc

FLAGS = -Wall -Wextra -Werror

DIR_S = srcs

DIR_O = obj

DIR_V = visualizer

SOURCES = check_fit.c filler.c get_piece.c heat_map.c read_info.c utils.c

V_SOURCES = visu.c visu_options.c visu_print.c visu_utils.c visu_heat.c \
			visu_make_heat.c

LIBFT = libft/libft.a

INC = includes/

V_INC = visualizer/

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJ = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

V_SRCS = $(addprefix $(DIR_V)/,$(V_SOURCES))

V_OBJ = $(addprefix $(DIR_O)/,$(V_SOURCES:.c=.o))

PROGRESS_CHAR = "\e[92m█\e[0m"

all: dirs $(NAME)

$(NAME): $(OBJ)
	@echo "\nCompiling library..."
	@cd libft && make
	@echo "Creating executable..."
	@$(CC) -o $(NAME) $(FLAGS) $(OBJ) $(LIBFT)
	@echo "$(NAME) created."

dirs:
	@echo "Creating object dir..."
	@mkdir -p $(DIR_O)

$(DIR_O)/%.o: $(DIR_S)/%.c
	@$(CC) $(FLAGS) -I $(INC) -o $@ -c $<
	@echo $(PROGRESS_CHAR)"\c"

visu:

$(V_NAME): $(V_OBJ)
	@echo "Compiling library..."
	@cd libft && make re
	@echo "Creating visualizer..."
	@$(CC) -o $(V_NAME) $(FLAGS) $(V_OBJ) $(LIBFT)

$(DIR_O)/%.o: $(DIR_V)/%.c
	@mkdir -p $(DIR_O)
	@$(CC) $(FLAGS) -I $(V_INC) -I $(INC) -o $@ -c $<

clean:
	@echo "Removing libft objects..."
	@cd libft && make clean
	@echo "Removing project objects..."
	@rm -f $(OBJ)
	@rm -f $(V_OBJ)
	@echo "Removing object directory..."
	@rm -rf $(DIR_O)

fclean: clean
	@echo "Removing libft.a..."
	@cd libft && make fclean
	@echo "Removing executable..."
	@rm -f $(NAME)
	@rm -f $(V_NAME)

re: fclean all

.PHONY: all clean fclean re
