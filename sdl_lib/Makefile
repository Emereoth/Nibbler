CC = clang++
NAME = SDL.so
DYLIB = -shared -fPIC
CFLAGS = -Wall -Werror -Wextra -std=c++11

LIB = -L $${HOME}/.brew/lib -lSDL2 -lSDL2_image -lSDL2_mixer
INCPATH = $${HOME}/.brew/include/SDL2 $${HOME}/.brew/include/SDL2_mixer  ../libmusic/inc
CPATH = src/
OPATH = obj/

CFILES = 	libSDL.cpp

OFILES = $(CFILES:.cpp=.o)
HFILES = inc/libSDL.hpp

INC = $(addprefix -I, $(INCPATH))
OBJ = $(addprefix $(OPATH), $(OFILES))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(DYLIB) $(LIB) $(OBJ) -o $(NAME) 

$(OPATH)%.o: $(CPATH)%.cpp $(HFILES)
	@mkdir -p $(OPATH)
	$(CC) $(CFLAGS) $(INC) $< -c -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all