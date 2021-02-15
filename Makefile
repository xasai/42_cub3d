NAME := cub3D
LIB := libft/libft.a
INC := -Iinclude
OBJ := $(subst src/,obj/,$(patsubst %.c,%.o,$(wildcard src/*.c)))
OBJDIR := obj/
VPATH := src
CC := gcc -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(LIB) $(OBJDIR) $(OBJ) 
	$(CC) $(OBJ) $(INC) -o $(NAME)

$(OBJDIR)%.o:%.c
	$(CC) -c $< $(INC) -o $@		

$(LIB):
	make -C libft/

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJ)
	make clean -C libft/

fclean: clean
	rm -f $(NAME)
	make fclean -C libft/

re: fclean all

.PHONY: re fclean clean $(LIB) all $(NAME)
