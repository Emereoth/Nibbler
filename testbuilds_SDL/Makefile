CC = clang++
NAME = testbuild_SDL
HPATH = ../inc/
SDL = ../sdl_lib
LIBGRAPH = -I../sdl_lib/SDL/include -L../sdl_lib/SDL/lib -lSDL2 -lSDL2_image -lSDL2_mixer
CFLAGS = -Wall -Werror -Wextra
CPATH = src/
OPATH = obj/
INC = $(addprefix -I, $(HPATH))
CFILES = main.cpp

OFILES = $(CFILES:.cpp=.o)

HFILES = ../inc/Api.class.hpp

OBJ = $(addprefix $(OPATH), $(OFILES))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(SDL)
	$(CC) $(CFLAGS) $(LIBGRAPH) $(OBJ) -o $(NAME)

$(OPATH)%.o: $(CPATH)%.cpp $(HFILES)
	$(CC) $(CFLAGS) $(INC) $< -c -o $@

clean:
	make -C $(SDL) clean
	rm -rf $(OBJ)

fclean: clean
	make -C $(SDL) fclean
	rm -rf $(NAME)

install:
	cd ../sdl_lib && make install

remove:
	make -C sdl_lib uninstall

re: fclean all

rebuild: remove install

