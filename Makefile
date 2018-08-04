NAME=libbaba
AR=ar
CC=gcc
CFLAGS=
INCLUDE=-Iinclude

SRC=$(wildcard src/*.c)
OBJ=$(patsubst src/%.c, obj/%.o, $(SRC))
SRC_TEST=$(wildcard test/*.c)
EXE_TEST=$(patsubst test/%.c, test/%, $(SRC_TEST))

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME).a $(OBJ)

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	@printf "[%s] \e[1;34m%s\e[m\n" $(CC) $<
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

test/%: test/%.c
	@$(CC) $(CFLAGS) $(INCLUDE) $< -o $@ -L. -lbaba
	@./$@
	@rm -f $@

clean:
	@rm -rf obj

fclean: clean
	@rm -f $(NAME).a

re: fclean all

test: all $(EXE_TEST)
