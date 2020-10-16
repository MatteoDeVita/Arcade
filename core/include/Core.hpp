/*
** EPITECH PROJECT, 2020
** arcade_temp
** File description:
** core
*/

#pragma once

#include <string>
#include <memory>

#include "../../games/nibbler/include/lib_arcade_nibbler.hpp"
#include "../../games/pacman/include/lib_arcade_pacman.hpp"
#include "../../lib/lib_arcade_ncurses/include/lib_arcade_ncurses.hpp"

class Core {
    private:
        typedef enum gameType {
            NIBBLER, PACMAN, GAME_NONE
        } gameType_t;
        typedef enum libType {
            NCURSES, SFML, SDL
        } libType_t;
        enum Input {
            INPUT_NONE,
            A, B, C, D, E, F, G, H, I, J, K, L, M,
            N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
            LEFT_ARROW, RIGHT_ARROW, UP_ARROW, DOWN_ARROW,
            ENTER, SPACE, DELETE, BACKSPACE, TAB, ESC, RETURN, ESCAPE
	    };
        std::string userName;
        libType_t libType;
        gameType_t gameType;
        void *gameLib;
        std::unique_ptr<IGraphicalsLib> (*castedGraphicalLib)();
        std::unique_ptr<IGraphicalsLib> graphicalLibHandler;
        std::unique_ptr<INibblerLib> (*castedNibblerLib)();
        std::unique_ptr<INibblerLib> nibblerLibHandler;
        std::unique_ptr<IPacmanLib> (*castedPacmanLib)();
        std::unique_ptr<IPacmanLib> pacmanLibHandler;
        void *graphicalLib;
        void play_game();
        void play_nibbler();
        void play_pacman();
        void play_menu();
        void draw_menu();
        void draw_string(int x, int y, unsigned char r, unsigned char g, unsigned char b, const std::string &string);
        void print_pacman_game();
        void print_nibbler_game(int *snakeArray);
        void set_new_graphical_lib(Core::libType_t newLibType);
        void switch_game();
    public:
        bool string_ends_with(const std::string &string, const std::string &end);
        Core(std::string &libFilePath);
};
