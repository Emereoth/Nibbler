CC = clang++
NAME = SDL.so
DYLIB = -shared -fPIC
LIBGRAPH = -L $${HOME}/.brew/lib -lSDL2 -lSDL2_image -lSDL2_mixer
SOUNDLIB = 
CFLAGS = -Wall -Werror -Wextra -std=c++11
CPATH = src/
OPATH = obj/
INC = $(addprefix -I, $(INCPATH))
CFILES = libSDL.cpp
INCPATH = $${HOME}/.brew/include/SDL2

OFILES = $(CFILES:.cpp=.o)

HFILES = inc/libSDL.hpp

OBJ = $(addprefix $(OPATH), $(OFILES))

.PHONY: all clean fclean re install uninstall reinstall

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(DYLIB) $(SOUNDLIB) $(LIBGRAPH) $(OBJ) -o $(NAME) 

$(OPATH)%.o: $(CPATH)%.cpp $(HFILES)
	$(CC) $(CFLAGS) $(INC) $< -c -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

install:
	brew install sdl2
	brew install sdl2_image
	brew install sdl2_mixer

uninstall:
	brew uninstall sdl2_mixer
	brew uninstall sdl2_image
	brew uninstall sdl2

reinstall: uninstall install