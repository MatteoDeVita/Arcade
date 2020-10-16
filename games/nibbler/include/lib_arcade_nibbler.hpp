/*
** EPITECH PROJECT, 2020
** arcade_temp
** File description:
** nibbler
*/

#pragma once

#include "../../../interfaces/INibblerLib.hpp"
#include "../../../lib/lib_arcade_ncurses/include/lib_arcade_ncurses.hpp"
#include "nibbler_structs.hpp"


class LibNibbler: public INibblerLib {
    private:
        apple_t apple;
        nibbler_player_t player;
        int score;
        char *str_int;
        int key;
        int **init_snake_tab() override;
        int **create_2dtab(int nb_cols, int nb_rows) override;
    public:
        LibNibbler();
        int collision(int *snakeArray) override;
        void handle_apple_life() override;
        void move_snake_head(int *snakeArray) override;
        void eat_apple(int *snakeArray) override;
        apple_t get_apple() override;
        nibbler_player_t get_player() override;
        nibbler_player_t *get__player_ptr() override;
        void move_Snake_Body(int *snakeArray, nibbler_player_t *player, int i) override;
        void write_scores(const char *username) override;
        int kbhit() override;
        void handle_input_pressed(int key) override;
        int *get_snake_array_ptr() override;
};

