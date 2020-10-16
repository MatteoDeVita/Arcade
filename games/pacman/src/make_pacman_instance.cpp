/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** make_pacman_instance
*/


#include <memory>

#include "lib_arcade_pacman.hpp"

#include "../../../interfaces/IPacmanLib.hpp"

std::unique_ptr<IPacmanLib> make_pacman_instance()
{
    return std::make_unique<LibPacman>();
}
