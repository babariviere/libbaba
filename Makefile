NAME=libbaba
AR=ar
CC=gcc
CFLAGS=
INCLUDE=-Iinclude

SRC=$(wildcard src/*.c)
OBJ=$(patsubst src/%.c, obj/%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME).a $(OBJ)

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	@printf "[%s] \e[1;34m%s\e[m\n" $(CC) $<
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@rm -rf obj

fclean: clean
	@rm $(NAME).a

re: fclean all
