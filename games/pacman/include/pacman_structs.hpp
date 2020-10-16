/*
** EPITECH PROJECT, 2020
** test_ncurses [WSL: Ubuntu-18.04]
** File description:
** pacman_pos_structs
*/

#pragma once

typedef struct ghost ghost;
struct ghost
{
    int x;
    int y;
    double speed;
    int weak;
};

typedef struct player player_t;
struct player
{
    int x;
    int y;
    int nb_mini_pacball_eat;
    double speed;
    int big_pacball_effect;
};

typedef struct direction direction;
struct direction
{
    int left;
    int right;
    int up;
    int down;
};
