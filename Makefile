##
## EPITECH PROJECT, 2019
## palindrome
## File description:
## Makefile
##

CXX	=	g++

CXXFLAGS	=  -I $(INCLUDE_PATH) -Wall -Wextra #-Werror

CORE_PATH	=	core/

GAMES_PATH	=	games/

LIB_PATH	=	lib/

NIBBLER_GAME_PATH	= $(GAMES_PATH)/nibbler/

PACMAN_GAME_PATH	=	$(GAMES_PATH)/pacman/

NCURSES_LIB_PATH	=	$(LIB_PATH)/lib_arcade_ncurses/

SDL_LIB_PATH	=	$(LIB_PATH)/lib_arcade_sdl/

SFML_LLIB_PATH	=	$(LIB_PATH)/lib_arcade_sfml/

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

all:
	@echo "$(BOLD)$(CYAN)\n\n\t-----STARTING COMPILATION-----\n\n$(YELLOW)"
	@make -C $(CORE_PATH)
	@make -C $(NIBBLER_GAME_PATH)
	@make -C $(PACMAN_GAME_PATH)
	@make -C $(NCURSES_LIB_PATH)
	@make -C $(SDL_LIB_PATH)
	@make -C $(SFML_LLIB_PATH)
	@echo "$(BOLD)$(GREEN)\n\n\t-----COMPILATION SUCCESSFUL-----"


core: games_and_graphicals
	make -C $(CORE_PATH)

games: graphicals	
	make -C $(NIBBLER_GAME_PATH)
	make -C $(PACMAN_GAME_PATH)

graphicals:
	make -C $(NCURSES_LIB_PATH)
	make -C $(SDL_LIB_PATH)
	make -C $(SFML_LLIB_PATH)

games_and_graphicals:
	make -C $(NIBBLER_GAME_PATH)
	make -C $(PACMAN_GAME_PATH)
	make -C $(NCURSES_LIB_PATH)
	make -C $(SDL_LIB_PATH)
	make -C $(SFML_LLIB_PATH)

clean:
	make clean -C $(NIBBLER_GAME_PATH)
	make clean -C $(PACMAN_GAME_PATH)
	make clean -C $(NCURSES_LIB_PATH)
	make clean -C $(SDL_LIB_PATH)
	make clean -C $(SFML_LLIB_PATH)
	@echo "$(BOLD)$(GREEN)\t-----WORKSPACE CLEANED-----"

fclean: clean
	make fclean -C $(NIBBLER_GAME_PATH)
	make fclean -C $(PACMAN_GAME_PATH)
	make fclean -C $(NCURSES_LIB_PATH)
	make fclean -C $(SDL_LIB_PATH)
	make fclean -C $(SFML_LLIB_PATH)
	rm -rf arcade
	@echo "$(BOLD)$(GREEN)\t-----WORKSPACE FCLEANED-----"

re: fclean all

.PHONY: clean fclean all re
