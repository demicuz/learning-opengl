NAME		:= trying-into-opengl

SRC_DIR		:= src

SRC			:= $(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/*/*.c)
OBJ			:= $(SRC:.c=.o)

# TODO set correct flags
CC			:= gcc
CPPFLAGS	:= -I include -MMD -MP
CFLAGS		:= -std=c11 -pedantic -O1 -g -Wall#-Wextra#-Werror
LDFLAGS		:=
LDLIBS		:= -lglfw -lGL

.PHONY: all bonus clean fclean re

all: $(NAME)

bonus: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) $(LDLIBS) -o $(NAME)

# Turns out you don't have to have a rule for object files. 'Make' uses CFLAGS
# and CPPFLAGS variables to compile .o files.
# %.o: %.c
# 	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	rm -vf $(OBJ)
	rm -vf $(OBJ:.o=.d)

fclean: clean
	rm -vf $(NAME)

re: fclean all

-include $(OBJ:.o=.d)
