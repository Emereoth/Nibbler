CC = clang++
NAME = snake
HPATH = inc/
SFML = sfml_lib
LINK_DYLIB = -Wl,-rpath $(SFML)/SFML/lib
CFLAGS = -Wall -Werror -Wextra
CPATH = src/
OPATH = obj/
INC = $(addprefix -I, $(HPATH))
CFILES = main.cpp

OFILES = $(CFILES:.cpp=.o)

HFILES = inc/Api.class.hpp

OBJ = $(addprefix $(OPATH), $(OFILES))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(SFML)
	$(CC) $(CFLAGS) $(LINK_DYLIB) $(OBJ) -o $(NAME)

$(OPATH)%.o: $(CPATH)%.cpp $(HFILES)
	$(CC) $(CFLAGS) $(INC) $< -c -o $@

clean:
	make -C $(SFML) clean
	rm -rf $(OBJ)

fclean: clean
	make -C $(SFML) fclean
	rm -rf $(NAME)

re: fclean all

