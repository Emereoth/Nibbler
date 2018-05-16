CC = clang++
NAME = SDL.so
# HPATH = inc/ SDL/include
DYLIB = -shared -fPIC
# LIBGRAPH = -LSDL/lib -lSDL-graphics -lSDL-window -lSDL-system -lSDL-audio
CFLAGS = -Wall -Werror -Wextra
LIBFLAGS = -I./SDL/include -L./SDL/lib
CPATH = src/
OPATH = obj/
# INC = $(addprefix -I, $(HPATH))
CFILES = libSDL.cpp

OFILES = $(CFILES:.cpp=.o)

HFILES = inc/libSDL.hpp

OBJ = $(addprefix $(OPATH), $(OFILES))

.PHONY: all clean fclean re install uninstall reinstall

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(DYLIB) $(LIBGRAPH) $(OBJ) -o $(NAME)

$(OPATH)%.o: $(CPATH)%.cpp $(HFILES)
	$(CC) $(CFLAGS) $(INC) $< -c -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

install:
	@wget https://libsdl.org/release/SDL2-2.0.8.tar.gz
	@tar -xf SDL2-2.0.8.tar.gz
	@rm -rf SDL2-2.0.8.tar.gz
	@mv SDL2-2.0.8 SDL
	@cd SDL && ./configure --prefix=${PWD}/SDL && make && make install

uninstall:
	@rm -rf SDL

reinstall: uninstall install
