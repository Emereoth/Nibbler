CC = clang++
NAME = SDL.so
DYLIB = -shared -fPIC
LIBGRAPH = -I./SDL/include -L./SDL/lib -lSDL2
CFLAGS = -Wall -Werror -Wextra
CPATH = src/
OPATH = obj/
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
	wget https://libsdl.org/release/SDL2-2.0.8.tar.gz
	tar -xf SDL2-2.0.8.tar.gz
	rm -rf SDL2-2.0.8.tar.gz
	mv SDL2-2.0.8 SDL && cd SDL && ./configure --prefix=${PWD}/SDL && make && make install
	wget https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.3.tar.gz
	tar -xf SDL2_image-2.0.3.tar.gz
	rm -rf SDL2_image-2.0.3.tar.gz
	mv SDL2_image-2.0.3 SDL_Image && cd SDL_Image && ./configure --prefix=${PWD}/SDL && make && make install
	cp SDL/include/SDL.h SDL/include/SDL_version.h SDL/include/begin_code.h SDL/include/close_code.h SDL_Image

uninstall:
	rm -rf SDL
	rm -rf SDL_Image

reinstall: uninstall install