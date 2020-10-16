/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** make_nibbler_instance
*/

#include <memory>

#include "lib_arcade_nibbler.hpp"

#include "../../../interfaces/INibblerLib.hpp"

std::unique_ptr<INibblerLib> make_nibbler_instance()
{
    return std::make_unique<LibNibbler>();
}
