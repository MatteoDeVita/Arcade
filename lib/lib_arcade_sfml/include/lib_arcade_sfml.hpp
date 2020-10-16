/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** lib_arcade_sfml
*/

#pragma once

#include <curses.h>
#include <memory>
#include <SFML/Graphics.hpp>

#include "../../../interfaces/IGraphicalsLib.hpp"

class LibSFML : public IGraphicalsLib {
    private:
        typedef enum player_dir {UP, RIGHT, DOWN, LEFT} player_dir_t;
        sf::RenderWindow *window;
        sf::Event event;
        sf::RectangleShape borderRectangle;
        sf::RectangleShape pacmanBorderRectangle;
        sf::RectangleShape nibblerBorderRectangle;
        sf::Font font;
        sf::Text text;
        sf::Sprite sprite;
        sf::Texture texture;
        player_dir_t player_dir;
        int key;
    public:
        LibSFML() = default;
        ~LibSFML() = default;
        void init() override;
        void deinit() override;
        void set_pixel(unsigned long x, unsigned long y, unsigned char r, unsigned char g, unsigned char b, char c) override;
        void clear(unsigned char r, unsigned char g, unsigned char b) override;
        int get_input_pressed() override;
        bool update() override;
};

namespace arcade {
	enum Input {
		NONE,
		A, B, C, D, E, F, G, H, I, J, K, L, M,
		N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		LEFT_ARROW, RIGHT_ARROW, UP_ARROW, DOWN_ARROW,
		ENTER, SPACE, DELETE, BACKSPACE, TAB, ESC, RETURN, ESCAPE
	};
};
