##
## GROUNDHOG PROJECT, 2024
## groundhog
## File description:
## Makefile
##

# -------------------------------------------------------------------------- #

CC ?= gcc
CPPFLAGS += -iquote./include
CFLAGS += -Wall -Wextra -Werror -g3

# -------------------------------------------------------------------------- #

SRC_DIR	 =	./src/
NAME =	groundhog
OBJ =				$(SRC:.c=.o)
SRC	=				$(SRC_DIR)main.c				\
					$(SRC_DIR)error_handling.c		\
					$(SRC_DIR)calculations.c		\
					$(SRC_DIR)utils.c				\
					$(LIB)							\

# -------------------------------------------------------------------------- #

LIB_DIR = ./src/lib/
LIB =				$(LIB_DIR)word_array_delim.c	\

# -------------------------------------------------------------------------- #

UTFILE = ./tests/unit_test.c
UTFLAGS = --coverage -lcriterion -lm -o
UTSRC = 			$(SRC_DIR)error_handling.c		\
					$(SRC_DIR)calculations.c		\
					$(SRC_DIR)utils.c				\
					$(LIB_DIR)word_array_delim.c	\

# -------------------------------------------------------------------------- #

RM = rm -f

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CPPFLAGS) $(CFLAGS) -lm

tests_run:
	$(CC) $(UTSRC) $(UTFILE) $(CPPFLAGS) $(UTFLAGS) unit_tests
	./unit_tests

tests_clean:
		$(RM) unit_tests*

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re:	 fclean all

.PHONY = all clean fclean re
