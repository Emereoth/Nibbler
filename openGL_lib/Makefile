CC = clang++
NAME = openGL.so
HPATH = inc/ GLFW/include $$HOME/.brew/include SOIL2/incs ../libmusic/inc/ $${HOME}/.brew/include/SDL2
DYLIB = -shared -fPIC
LIBGRAPH = -framework openGL -framework Cocoa -framework IOKit -framework CoreVideo -L ~/.brew/lib/ -lGLEW -lSDL2 -lSDL2_mixer
CFLAGS = -Wall -Werror -Wextra -std=c++11
CPATH = src/
OPATH = obj/
INC = $(addprefix -I, $(HPATH))
CFILES =	libOpenGL.cpp		\
			audio.cpp

OFILES = $(CFILES:.cpp=.o)

HFILES = inc/libOpenGL.hpp

OBJ = $(addprefix $(OPATH), $(OFILES))

.PHONY: all clean fclean re

all: import $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(DYLIB) $(LIBGRAPH) $(OBJ) GLFW/src/libglfw3.a  SOIL2/libSOIL2.a -o $(NAME)
	@rm src/audio.cpp

$(OPATH)%.o: $(CPATH)%.cpp $(HFILES)
	@mkdir -p $(OPATH)
	$(CC) $(CFLAGS) $(INC) $< -c -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

import:
	@cp ../libmusic/src/audio.cpp src

install:
	brew install glew
	wget https://github.com/glfw/glfw/releases/download/3.2.1/glfw-3.2.1.zip
	tar -xf glfw-3.2.1.zip
	rm -rf glfw-3.2.1.zip
	mv glfw-3.2.1 GLFW
	cd GLFW && cmake . && make
	git clone https://github.com/alelievr/SOIL2.git
	cd SOIL2 && make

uninstall:
	brew uninstall glew

remove:
	rm -rf GLFW
	rm -rf SOIL2

re: fclean all
