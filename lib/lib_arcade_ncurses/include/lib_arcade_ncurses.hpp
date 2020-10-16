/*
** EPITECH PROJECT, 2020
** arcade_temp
** File description:
** lib_arcade_ncurses
*/

#pragma once

#include <curses.h>
#include <memory>

#include "../../../interfaces/IGraphicalsLib.hpp"

#define NORMAL_COLOR 1
#define RED_COLOR 2
#define GREEN_COLOR 3
#define BLUE_COLOR 4
#define YELLOW_COLOR 5

class LibNCurses : public IGraphicalsLib
{
    public:
        LibNCurses() = default;
        ~LibNCurses() override = default;
        void init() override;
        void deinit() override;
        void set_pixel(unsigned long x, unsigned long y, unsigned char r, unsigned char g, unsigned char b, char ncurse_char) override;
        void clear(unsigned char r, unsigned char g, unsigned char b) override;
        int get_input_pressed() override;
        bool update() override;
};

namespace ncurses_args {
    struct color {
        unsigned char b;
        unsigned char g;
        unsigned char r;
    };
}

namespace arcade {
	enum Input {
		NONE,
		A, B, C, D, E, F, G, H, I, J, K, L, M,
		N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		LEFT_ARROW, RIGHT_ARROW, UP_ARROW, DOWN_ARROW,
		ENTER, SPACE, DELETE, BACKSPACE, TAB, ESC, RETURN, ESCAPE
	};
};
