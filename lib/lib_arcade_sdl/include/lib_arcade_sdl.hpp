/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** lib_arcade_sdl
*/

#include <SDL2/SDL.h>

#include "../../../interfaces/IGraphicalsLib.hpp"

class LibSDL : public IGraphicalsLib
{
    private:
        typedef enum player_dir {UP, RIGHT, DOWN, LEFT} player_dir_t;
        player_dir_t _player_dir;
        SDL_Window *_window;
        SDL_Event _event;
        SDL_Renderer *_renderer;
        SDL_Surface *_surface;
        SDL_Texture *_texture;
        SDL_Rect _rect;
        SDL_Rect _spritePos;
        int _key;
        void _set_renderer_draw_color(Uint8 r, Uint8 g, Uint8 b);
        SDL_Rect _get_letter_texture_rect(char c); // ! c must be lowercase
        void _set_key();
    public:
        LibSDL() = default;
        ~LibSDL() override = default;
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
