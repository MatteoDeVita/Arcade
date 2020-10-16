/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** lib_arcade_pacman
*/

#pragma once

#include "pacman_structs.hpp"
#include "../../../interfaces/IPacmanLib.hpp"

class LibPacman : public IPacmanLib {
    private:
        int score;
        int nb_cols;
        int nb_rows;
        int door_status;
        player_t player;
        direction active_direction;
        ghost ghost1;
        ghost ghost2;
        char **map;
        clock_t c_update;
        clock_t c_player_speed;
        clock_t c_start_boost_effect_time;
        clock_t ghost_speed_clock;
        clock_t spwan_ghost_clock;
        double time_player;
        double time_boost;
        double ghost_door_timer;
        double ghost_timer;
        double ghost_speed;
        int ghost_move_order1;
        int ghost_move_order2;
        double playerspeed;
        direction ghost1_direction;
        direction ghost2_direction;
        void right_key_action() override;
        void left_key_action() override;
        void down_key_action() override;
        void up_key_action() override;
        int ghost_move_ia1() override;
        int ghost_move_ia2() override;
        int random_nb(int max, int min) override;
        int right_ghost(struct ghost *ghost, int *move_order) override;
        int left_ghost(struct ghost *ghost, int *move_order) override;
        int down_ghost(struct ghost *ghost, int *move_order) override;
        int up_ghost(struct ghost *ghost, int *move_order) override;        
    public:        
        LibPacman();
        void init_map() override;
        char **create_2dtab() override;
        int spot_win() override;
        void update_time() override;
        int get_nb_cols() override;
        int get_nb_rows() override;
        char **get_map() override;
        int get_door_status() override;
        void open_ghost_door() override;
        void find_player() override;
        void active_direction_func(int key) override;
        double get_time_player() override;
        player_t get_player() override;
        void update_player() override;
        void active_player_movement();
        void write_scores(const char *username) override;
        void close_ghost_door_after_spawn() override;
        void handle_player_super_mode() override;
        int handle_ghost() override;
};
