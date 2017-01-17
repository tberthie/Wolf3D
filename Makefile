SRCS = main.c \
	   setup.c \
	   run.c \
	   render.c \
	   utl.c

OBJS = $(addprefix srcs/,$(SRCS:.c=.o))

NAME = wolf3d
CC = gcc
FLAGS = -Wall -Wextra
INCS = includes -I libft/includes

GREEN = \x1b[32m
EOC = \x1b[0m

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)[compiling libft]$(EOC)"
	@make -C libft
	@make -C minilibx
	@gcc $(FLAGS) -o $(NAME) libft/libft.a minilibx/libmlx.a $(OBJS) \
	-framework OpenGL -framework AppKit
	@echo "$(GREEN)[$(NAME)]$(EOC)"

srcs/%.o: srcs/%.c
	@$(CC) $(FLAGS) -I $(INCS) -I minilibx -o $@ -c $<
	@echo "[$@]"

clean:
	@make clean -C libft
	@rm -f $(OBJS)
	@echo "$(GREEN)[objs removed]$(EOC)"

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)
	@echo "$(GREEN)[workspace clean]$(EOC)"

re: fclean all
