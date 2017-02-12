SRCS = $(addsuffix .c, main setup run render utl walls textures minimap)

OBJS = $(addprefix objs/,$(SRCS:.c=.o))

NAME = wolf3d
CC = gcc
FLAGS = -Wall -Wextra -O3
INCS = -I includes -I libft/includes -I SDL

all: objs $(NAME)

objs:
	mkdir objs

$(NAME): $(OBJS)
	make -C libft
	gcc $(INCS) $(FLAGS) -o $(NAME) libft/libft.a SDL/libSDL2-2.0.0.dylib $(OBJS)

objs/%.o: srcs/%.c
	$(CC) $(FLAGS) $(INCS) -o $@ -c $<

clean:
	make clean -C libft
	rm -rf objs

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all
