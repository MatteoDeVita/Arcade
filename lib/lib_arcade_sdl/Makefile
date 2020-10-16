##
## EPITECH PROJECT, 2019
## core arcade
## File description:
## Makefile
##

CXX	=	g++

INCLUDE_PATH	=	include/

CXXFLAGS	= `pkg-config --cflags --libs sdl2` -Wall -Wextra -fPIC -I $(INCLUDE_PATH) # -Werror

LIB_NAME	=	lib_arcade_sdl.so

SRC	=	$(wildcard src/*.cpp)

OBJ	=	$(SRC:.cpp=.o)

END         =   \033[0m
BOLD        =   \033[1m
GREY        =   \033[30m
RED         =   \033[31m
GREEN       =   \033[32m
BLINK       =   \033[32;5m
YELLOW      =   \033[33m
BLUE        =   \033[34m
PURPLE      =   \033[35m
CYAN        =   \033[36m
WHITE       =   \033[37m

all: $(LIB_NAME)

$(LIB_NAME): $(OBJ)
	@$(CXX) -c $(SRC) $(CXXFLAGS)
	@mv *.o src/
	$(CXX) -shared -o $(LIB_NAME) $(OBJ) `pkg-config --cflags --libs sdl2` -ltinfo
	export LD_LIBRARY_PATH=$(shell pwd)/$(LIB_NAME)
	@mv $(LIB_NAME) ../

clean:
	@rm -rf $(OBJ) ../$(LIB_NAME)
	@echo "$(BOLD)$(GREEN)\t-----WORKSPACE CLEANED-----"

fclean: clean
	@rm -rf $(LIB_NAME)
	@echo "$(BOLD)$(GREEN)\t-----WORKSPACE FCLEANED-----"

re: fclean all

.PHONY: clean fclean all re
