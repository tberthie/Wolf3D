SRCS = main.c \
	   setup.c \
	   run.c \
	   render.c \
	   utl.c

OBJS = $(addprefix srcs/,$(SRCS:.c=.o))

NAME = wolf3d
CC = gcc
FLAGS = -Wall -Wextra -O3
INCS = includes -I libft/includes

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	make -C minilibx
	gcc $(FLAGS) -o $(NAME) libft/libft.a minilibx/libmlx.a $(OBJS) \
	-framework OpenGL -framework AppKit

srcs/%.o: srcs/%.c
	$(CC) $(FLAGS) -I $(INCS) -I minilibx -o $@ -c $<

clean:
	make clean -C libft
	rm -f $(OBJS)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all
