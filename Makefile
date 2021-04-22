###################################################################
NAME := cub3D

SRC := $(shell find src/ -type f -name '*.c')
OBJ := $(subst src/, obj/, $(SRC:.c=.o)) 

LIBFT := lib/libft/libft.a
LIB_MLX := lib/mlx_linux/libmlx_Linux.a 
LIB := $(LIBFT) $(LIB_MLX) -Llib/mlx_linux -lmlx_Linux -Llib/libft  
INC := -Iinclude/ -Ilib/mlx_linux -Ilib/libft/include -I/usr/share
 
VPATH := src/															
OBJPATH := obj/
OBJDIR := $(subst src/, obj/, $(shell find src/* -type d))
																   
CC := gcc
FLAG := -Wall -Wextra -Werror -g3 -std=c99						   
####################################################################


all: $(NAME) test

debug: $(NAME)
	gdb --args $(NAME) map/1.cub

test:
	./$(NAME)  map/1.cub

$(NAME): $(LIBFT) $(LIB_MLX) $(OBJDIR) $(OBJ) 
	$(CC) $(FLAG) $(OBJ) $(INC) $(LIB) -lXext -lX11 -lm -lz -o $(NAME) 

$(OBJPATH)%.o:%.c
	$(CC) $(INC) $(FLAG) -c $< -o $@

$(LIBFT): 
	make -C $(dir $(LIBFT))

$(LIB_MLX): 
	make -C $(dir $(LIB_MLX))

$(OBJDIR): 
	mkdir -p $(OBJDIR) 

clean:
	rm -rf obj/
	make clean -C lib/libft/

fclean: clean
	rm -fr $(NAME) 
	make fclean -C $(dir $(LIBFT)) 

re: fclean all

.PHONY: re fclean clean $(LIBFT) all $(NAME) test
