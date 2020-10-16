/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** INibblerLib
*/

#pragma once

#include "../games/nibbler/include/nibbler_structs.hpp"

#include <memory>

struct INibblerLib {
    apple_t apple;
    nibbler_player_t player;
    int score;
    char *str_int;
    virtual ~INibblerLib() = default;
    virtual int **init_snake_tab() = 0;
    virtual int **create_2dtab(int nb_cols, int nb_rows) = 0;
    virtual int collision(int *snakeArray) = 0;
    virtual void handle_apple_life() = 0;
    virtual void move_snake_head(int *snakeArray) = 0;
    virtual void eat_apple(int *snakeArray) = 0;
    virtual apple_t get_apple() = 0;
    virtual nibbler_player_t get_player() = 0;
    virtual nibbler_player_t *get__player_ptr() = 0;
    virtual void move_Snake_Body(int *snakeArray, nibbler_player_t *player, int i) = 0;
    virtual void write_scores(const char *username) = 0;
    virtual int kbhit() = 0;
    virtual void handle_input_pressed(int key) = 0;
    virtual int *get_snake_array_ptr() = 0;
};

extern "C" std::unique_ptr<INibblerLib> make_nibbler_instance();

