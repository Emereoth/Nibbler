CC = clang++
NAME = openGL.so
HPATH = inc/ GLFW/include /Users/rvievill/.brew/include
DYLIB = -shared -fPIC
LIBGRAPH = -framework openGL -framework Cocoa -framework IOKit -framework CoreVideo -L ~/.brew/lib/ -lGLEW
CFLAGS = -Wall -Werror -Wextra
CPATH = src/
OPATH = obj/
INC = $(addprefix -I, $(HPATH))
CFILES = libOpenGL.cpp

OFILES = $(CFILES:.cpp=.o)

HFILES = inc/libOpenGL.hpp

OBJ = $(addprefix $(OPATH), $(OFILES))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(DYLIB) $(LIBGRAPH) $(OBJ) GLFW/src/libglfw3.a -o $(NAME)

$(OPATH)%.o: $(CPATH)%.cpp $(HFILES)
	@mkdir -p $(OPATH)
	$(CC) $(CFLAGS) $(INC) $< -c -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf SFML
	rm -rf $(NAME)

install:
	wget https://github.com/glfw/glfw/releases/download/3.2.1/glfw-3.2.1.zip
	tar -xf glfw-3.2.1.zip
	rm -rf glfw-3.2.1.zip
	mv glfw-3.2.1 GLFW
	cd GLFW && cmake . && make

remove:
	rm -rf GLFW

re: remove install fclean all