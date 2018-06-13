CC = clang++
NAME = SDL.so
DYLIB = -shared -fPIC
CFLAGS = -Wall -Werror -Wextra -std=c++11

LIB = -L $${HOME}/.brew/lib -lSDL2 -lSDL2_image
INCPATH = $${HOME}/.brew/include/SDL2  ../libmusic/inc
CPATH = src/
OPATH = obj/

CFILES = 	libSDL.cpp \
			audio.cpp
OFILES = $(CFILES:.cpp=.o)
HFILES = inc/libSDL.hpp

INC = $(addprefix -I, $(INCPATH))
OBJ = $(addprefix $(OPATH), $(OFILES))

.PHONY: all clean fclean re install uninstall reinstall

all: import $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(DYLIB) $(LIB) $(OBJ) -o $(NAME) 
	@rm src/audio.cpp

$(OPATH)%.o: $(CPATH)%.cpp $(HFILES)
	@mkdir -p $(OPATH)
	$(CC) $(CFLAGS) $(INC) $< -c -o $@

import:
	@cp ../libmusic/src/audio.cpp src

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

install:
	brew install sdl2
	brew install sdl2_image

uninstall:
	brew uninstall sdl2_image
	brew uninstall sdl2

reinstall: uninstall install