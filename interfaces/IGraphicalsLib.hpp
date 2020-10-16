/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** IGraphicalsLib
*/

#pragma once

#include <memory>

struct IGraphicalsLib {
    virtual ~IGraphicalsLib() = default;
    virtual void init() = 0;
    virtual void deinit() = 0;
    virtual void set_pixel(unsigned long x, unsigned long y, unsigned char r, unsigned char g, unsigned char b, char ncurse_char) = 0;
    virtual void clear(unsigned char r, unsigned char g, unsigned char b) = 0;
    virtual int get_input_pressed() = 0;
    virtual bool update() = 0;    
};

extern "C" std::unique_ptr<IGraphicalsLib> make_graphics_instance();
