CC = clang++
NAME = nibbler
HPATH = inc/
SFML = sfml_lib
SDL = sdl_lib
OPENGL = openGL_lib
LINK_DYLIB = -Wl,-rpath $(SFML)/SFML/lib
CFLAGS = -Wall -Werror -Wextra -std=c++11 -g
CPATH = src/
OPATH = obj/
INC = $(addprefix -I, $(HPATH))
CFILES =	main.cpp			\
			Map.class.cpp		\
			Snake.class.cpp		\
			Nibbler.class.cpp

OFILES = $(CFILES:.cpp=.o)

HFILES = inc/Api.class.hpp

OBJ = $(addprefix $(OPATH), $(OFILES))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(SFML)
	make -C $(SDL)
	make -C $(OPENGL)
	$(CC) $(CFLAGS) $(LINK_DYLIB) $(OBJ) -o $(NAME)

$(OPATH)%.o: $(CPATH)%.cpp $(HFILES)
	$(CC) $(CFLAGS) $(INC) $< -c -o $@

clean:
	make -C $(SFML) clean
	make -C $(SDL) clean
	make -C $(OPENGL) clean
	rm -rf $(OBJ)

fclean: clean
	make -C $(SFML) fclean
	make -C $(SDL) fclean
	make -C $(OPENGL) fclean
	rm -rf $(NAME)

install:
	make -C sfml_lib install
	make -C openGL_lib install
	cd sdl_lib && make install

remove:
	make -C openGL_lib remove
	make -C sfml_lib remove
	make -C sdl_lib uninstall

re: fclean all

rebuild: remove install

