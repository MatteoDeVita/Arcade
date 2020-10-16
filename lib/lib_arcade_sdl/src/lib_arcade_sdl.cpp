/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** lib_arcade_sdl
*/

#include <SDL2/SDL.h>

#include "lib_arcade_sdl.hpp"
#include <error.h>

#include <iostream>

void LibSDL::init() {
    this->_window = SDL_CreateWindow(
        "SDL Window",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        852, 800,
        SDL_WINDOW_SHOWN
    );
    if ((this->_renderer = SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_ACCELERATED)) == NULL)
        error(84 , 0, "Can't load renderer");
    if ((this->_surface = SDL_LoadBMP("./utils/texture.bmp")) == NULL)
        error(84, 0, "Can't load surface");
    if ((this->_texture = SDL_CreateTextureFromSurface(this->_renderer, this->_surface)) == NULL)
        error(84, 0, "Can't laod texture");
    this->_key = -1;
    this->_player_dir = LibSDL::player_dir_t::RIGHT;
}

void LibSDL::deinit() {
    SDL_DestroyTexture(this->_texture);
    SDL_DestroyRenderer(this->_renderer);    
    SDL_DestroyWindow(this->_window);
    SDL_Quit();    
}

void LibSDL::set_pixel(unsigned long x, unsigned long y, unsigned char r, unsigned char g, unsigned char b, char c) {
    if (c == 'X') {
        this->_rect = (SDL_Rect) {.x = (int) (11 * x), .y = (int) (11 * y), .w = 11, .h = 11};
        this->_set_renderer_draw_color(125, 125, 125);
        SDL_RenderFillRect(this->_renderer, &this->_rect);
    }
    else if (c == '#' && b != 254) {        
        this->_rect = (SDL_Rect) {.x = (int) (25 * x), .y = (int) (25 * y), .w = 25, .h = 25};
        this->_set_renderer_draw_color(0, 0, 255);
        SDL_RenderFillRect(this->_renderer, &this->_rect);
    }
    else if (c == '#' && b == 254) {
        this->_rect = (SDL_Rect) {.x = (int) (10 * x), .y = (int) (10 * y), .w = 10, .h = 10};
        this->_set_renderer_draw_color(0, 0, 255);
        SDL_RenderFillRect(this->_renderer, &this->_rect);
    }
    else if (c == 'S' && r == 254) {
        this->_rect = (SDL_Rect) {.x = 46, .y = 56, .w = 17, .h = 16};
        this->_spritePos = (SDL_Rect) {.x = (int) (10 * x), .y = (int) (10 * y), .w = (int) (17), .h = (int) (16)};
        SDL_RenderCopy(this->_renderer, this->_texture, &this->_rect, &this->_spritePos);
    }
    else if (c == 'O' && r == 254) {
        this->_rect = (SDL_Rect) {.x = 65, .y = 56, .w = 19, .h = 18};
        this->_spritePos = (SDL_Rect) {.x = (int) (10 * x), .y = (int) (10 * y), .w = (int) (19), .h = (int) (18)};
        SDL_RenderCopy(this->_renderer, this->_texture, &this->_rect, &this->_spritePos);
    }
    else if (c == 'A') {
        this->_rect = (SDL_Rect) {.x = 86, .y = 56, .w = 16, .h = 19};
        this->_spritePos = (SDL_Rect) {.x = (int) (10 * x), .y = (int) (10 * y), .w = (int) (16), .h = (int) (19)};
        SDL_RenderCopy(this->_renderer, this->_texture, &this->_rect, &this->_spritePos);
    }
    else if (c == '.') {
        this->_rect = (SDL_Rect) {.x = 0, .y = 0, .w = 37, .h = 37};
        this->_spritePos = (SDL_Rect) {.x = (int) (25.5 * x), .y = (int) (25.5 * y), .w = (int) (37 * 0.45), .h = (int) (37 * 0.45)};
        SDL_RenderCopy(this->_renderer, this->_texture, &this->_rect, &this->_spritePos);
    }
    else if (c == 'O') {
        this->_rect = (SDL_Rect) {.x = 37, .y = 0, .w = 20, .h = 20};
        this->_spritePos = (SDL_Rect) {.x = (int) (25 * x), .y = (int) (25 * y), .w = (int) (20 * 1.14), .h = (int) (20 * 1.14)};
        SDL_RenderCopy(this->_renderer, this->_texture, &this->_rect, &this->_spritePos);
    }
    else if (c == 'P' && g != 255) {
        if (this->_player_dir == LibSDL::player_dir_t::UP) {
            this->_rect = (SDL_Rect) {.x = 154, .y = 5, .w = 37, .h = 31};
            this->_spritePos = (SDL_Rect) {.x = (int) (25 * x), .y = (int) (25 * y), .w = (int) (0.68 * 37), .h = (int) (0.68 * 31)};

        }
        else if (this->_player_dir == LibSDL::player_dir_t::RIGHT) {
            this->_rect = (SDL_Rect) {.x = 57, .y = 0, .w = 30, .h = 38};
            this->_spritePos = (SDL_Rect) {.x = (int) (25 * x), .y = (int) (25 * y), .w = (int) (0.68 * 30), .h = (int) (0.68 * 38)};
        }
        else if (this->_player_dir == LibSDL::player_dir_t::DOWN) {
            this->_rect = (SDL_Rect) {.x = 87, .y = 3, .w = 37, .h = 30};
            this->_spritePos = (SDL_Rect) {.x = (int) (25 * x), .y = (int) (25 * y), .w = (int) (0.68 * 37), .h = (int) (0.68 * 30)};

        }
        else if (this->_player_dir == LibSDL::player_dir_t::LEFT) {
            this->_rect = (SDL_Rect) {.x = 124, .y = 0, .w = 30, .h = 38};
            this->_spritePos = (SDL_Rect) {.x = (int) (25 * x), .y = (int) (25 * y), .w = (int) (0.68 * 30), .h = (int) (0.68 * 38)};
        }
        SDL_RenderCopy(this->_renderer, this->_texture, &this->_rect, &this->_spritePos);
    }
    else if (c == 'g') {
            this->_rect = (SDL_Rect) {.x = 193, .y = 0, .w = 38, .h = 39};
            this->_spritePos = (SDL_Rect) {.x = (int) (25 * x), .y = (int) (25 * y), .w = (int) (0.68 * 38), .h = (int) (0.68 * 39)};
            SDL_RenderCopy(this->_renderer, this->_texture, &this->_rect, &this->_spritePos);
    }
    else if (c == 'G' && b == 255 && r == 0 && g == 0) {
        this->_rect = (SDL_Rect) {.x = 231, .y = 0, .w = 37, .h = 38};
        this->_spritePos = (SDL_Rect) {.x = (int) (25 * x), .y = (int) (25 * y), .w = (int) (0.68 * 38), .h = (int) (0.68 * 39)};
        SDL_RenderCopy(this->_renderer, this->_texture, &this->_rect, &this->_spritePos);
    }
    else {
        this->_rect = _get_letter_texture_rect((c >= 'A' && c <= 'Z' ? c + 32 : c));
        this->_spritePos = (SDL_Rect) {.x = (int) (11 * x), .y = (int) (11 *  y), .w = this->_rect.w, .h = this->_rect.h};
        SDL_RenderCopy(this->_renderer, this->_texture, &this->_rect, &this->_spritePos);
    }
}

void LibSDL::clear(unsigned char r, unsigned char g, unsigned char b) {
    this->_set_renderer_draw_color(r, g, b);
    SDL_RenderClear(this->_renderer);
}

int LibSDL::get_input_pressed() {
    int key = this->_key;

    this->_key = arcade::Input::NONE;
    return key;
}

bool LibSDL::update() {
    while (SDL_PollEvent(&this->_event)) {
        switch (this->_event.type) {
            case SDL_QUIT:
                return false;
            case SDL_KEYDOWN:
                this->_set_key();
                break;
            default:
                break;
        }
    }
    SDL_RenderPresent(this->_renderer);
    return true;
}

void LibSDL::_set_key()
{
    if (this->_event.key.keysym.sym >= SDLK_a && this->_event.key.keysym.sym <= SDLK_z) {
        this->_key = this->_event.key.keysym.sym - (SDLK_a - 1);
    }
    else if (this->_event.key.keysym.sym == SDLK_BACKSPACE)
        this->_key = arcade::Input::BACKSPACE;
    else if (this->_event.key.keysym.sym == SDLK_UP) {
        this->_key = arcade::Input::UP_ARROW;
        this->_player_dir = LibSDL::player_dir_t::UP;
    }
    else if (this->_event.key.keysym.sym == SDLK_RIGHT) {
        this->_key = arcade::Input::RIGHT_ARROW;
        this->_player_dir = LibSDL::player_dir_t::RIGHT;
    }
    else if (this->_event.key.keysym.sym == SDLK_DOWN) {
        this->_key = arcade::Input::DOWN_ARROW;
        this->_player_dir = LibSDL::player_dir_t::DOWN;
    }
    else if (this->_event.key.keysym.sym == SDLK_LEFT) {
        this->_key = arcade::Input::LEFT_ARROW;
        this->_player_dir = LibSDL::player_dir_t::LEFT;
    }
}

void LibSDL::_set_renderer_draw_color(Uint8 r, Uint8 g, Uint8 b)
{
    if (SDL_SetRenderDrawColor(this->_renderer, r, g, b, 255) == -1)
        error(84, 0, "Can't initializerender draw color");
}

SDL_Rect LibSDL::_get_letter_texture_rect(char c)
{
    switch (c) {
        case 'a':
            return (SDL_Rect) {.x = 1, .y = 41, .w = 11, .h = 13};
        case 'b':
            return (SDL_Rect) {.x = 13, .y = 41, .w = 11, .h = 13};
        case 'c':
            return (SDL_Rect) {.x = 24, .y = 41, .w = 11, .h = 13};
        case 'd':
            return (SDL_Rect) {.x = 36, .y = 41, .w = 10, .h = 13};
        case 'e':
            return (SDL_Rect) {.x = 47, .y = 41, .w = 11, .h = 13};
        case 'f':
            return (SDL_Rect) {.x = 58, .y = 41, .w = 11, .h = 13};
        case 'g':
            return (SDL_Rect) {.x = 70, .y = 41, .w = 11, .h = 13};
        case 'h':
            return (SDL_Rect) {.x = 81, .y = 41, .w = 11, .h = 13};
        case 'i':
            return (SDL_Rect) {.x = 94, .y = 41, .w = 10, .h = 13};
        case 'j':
            return (SDL_Rect) {.x = 104, .y = 41, .w = 11, .h = 13};
        case 'k':
            return (SDL_Rect) {.x = 116, .y = 41, .w = 11, .h = 13};
        case 'l':
            return (SDL_Rect) {.x = 127, .y = 41, .w = 11, .h = 13};
        case 'm':
            return (SDL_Rect) {.x = 138, .y = 41, .w = 11, .h = 13};
        case 'n':
            return (SDL_Rect) {.x = 150, .y = 41, .w = 11, .h = 13};
        case 'o':
            return (SDL_Rect) {.x = 162, .y = 41, .w = 10, .h = 13};
        case 'p':
            return (SDL_Rect) {.x = 173, .y = 41, .w = 11, .h = 13};
        case 'q':
            return (SDL_Rect) {.x = 184, .y = 41, .w = 11, .h = 13};
        case 'r':
            return (SDL_Rect) {.x = 196, .y = 41, .w = 11, .h = 13};
        case 's':
            return (SDL_Rect) {.x = 207, .y = 41, .w = 11, .h = 13};
        case 't':
            return (SDL_Rect) {.x = 220, .y = 41, .w = 10, .h = 13};
        case 'u':
            return (SDL_Rect) {.x = 230, .y = 41, .w = 11, .h = 13};
        case 'v':
            return (SDL_Rect) {.x = 242, .y = 41, .w = 11, .h = 13};
        case 'w':
            return (SDL_Rect) {.x = 253, .y = 41, .w = 11, .h = 13};
        case 'x':
            return (SDL_Rect) {.x = 265, .y = 41, .w = 11, .h = 13};
        case 'y':
            return (SDL_Rect) {.x = 278, .y = 41, .w = 9, .h = 13};
        case 'z':
            return (SDL_Rect) {.x = 288, .y = 41, .w = 11, .h = 13};
        case '-':
            return (SDL_Rect) {.x = 1, .y = 55, .w = 11, .h = 13};
        case '>':
            return (SDL_Rect) {.x = 13, .y = 55, .w = 11, .h = 13};
        case '!':
            return (SDL_Rect) {.x = 26, .y = 56, .w = 7, .h = 12};
        case ':':
            return (SDL_Rect) {.x = 37, .y = 55, .w = 6, .h = 13};
    }
    return (SDL_Rect) {0, 0, 0, 0};
}
