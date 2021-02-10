NAME := cub3D

SRC := $(wildcard src/*.c)
OBJ := $(patsubst %c,%o,$(SRC))

LIB := libft/libft.a
LIBSRC := $(wildcard libft/*.c)

INC := -I include/

GCC := gcc -Wall -Wextra -Werror -g 

$(NAME): all

all: $(LIB) $(OBJ) $(LIBSRC)
	$(GCC) $(OBJ) $(INC) $(LIB) -o $(NAME)	

%.o:%.c include/cub3d.h
	$(GCC) $(INC) -c $< -o $@

$(LIBSRC):
	make -C libft/
$(LIB):
	make -C libft/

clean:
	rm -rf $(OBJ)
	make clean -C libft/

fclean:
	rm -f $(NAME)
	make fclean -C libft/

re: fclean all

.PHONY: re fclean clean $(LIB) all $(NAME)
