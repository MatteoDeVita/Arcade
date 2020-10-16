/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** make_graphics_instance
*/

#include <memory>

#include "lib_arcade_sdl.hpp"

#include "../../../interfaces/IGraphicalsLib.hpp"

std::unique_ptr<IGraphicalsLib> make_graphics_instance()
{
    return std::make_unique<LibSDL>();
}

