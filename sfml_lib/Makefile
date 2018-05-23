CC = clang++
NAME = sfml.so
HPATH = inc/ SFML/include
DYLIB = -shared -fPIC
LIBGRAPH = -LSFML/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
CFLAGS = -Wall -Werror -Wextra -std=c++14
CPATH = src/
OPATH = obj/
INC = $(addprefix -I, $(HPATH))
CFILES = libSFML.cpp

OFILES = $(CFILES:.cpp=.o)

HFILES = inc/libSFML.hpp

OBJ = $(addprefix $(OPATH), $(OFILES))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(DYLIB) $(LIBGRAPH) $(OBJ) -o $(NAME)

$(OPATH)%.o: $(CPATH)%.cpp $(HFILES)
	@mkdir -p $(OPATH)
	$(CC) $(CFLAGS) $(INC) $< -c -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

install:
	wget https://www.sfml-dev.org/files/SFML-2.4.2-osx-clang.tar.gz
	tar -xf SFML-2.4.2-osx-clang.tar.gz
	mv SFML-2.4.2-osx-clang SFML
	cp -r SFML/extlibs/* SFML/Frameworks/
	rm -rf SFML-2.4.2-osx-clang.tar.gz

remove:
	rm -rf SFML

re: remove install fclean all
