/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** IPacmanLib
*/

#pragma once

#include <memory>
#include <time.h>

#include "../games/pacman/include/pacman_structs.hpp"

struct IPacmanLib {
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
    virtual ~IPacmanLib() = default;
    virtual void init_map() = 0;
    virtual char **create_2dtab() = 0;
    virtual int spot_win() = 0;
    virtual void update_time() = 0;
    virtual int get_nb_cols() = 0;
    virtual int get_nb_rows() = 0;
    virtual char **get_map() = 0;
    virtual int get_door_status() = 0;
    virtual void open_ghost_door() = 0;
    virtual void find_player() = 0;
    virtual void active_direction_func(int key) = 0;
    virtual double get_time_player() = 0;
    virtual player_t get_player() = 0;
    virtual void update_player() = 0;
    virtual void active_player_movement() = 0;
    virtual void right_key_action() = 0;
    virtual void left_key_action() = 0;
    virtual void down_key_action() = 0;
    virtual void up_key_action() = 0;
    virtual void close_ghost_door_after_spawn() = 0;
    virtual void handle_player_super_mode() = 0;
    virtual int handle_ghost() = 0;
    virtual int ghost_move_ia1() = 0;
    virtual int ghost_move_ia2() = 0;
    virtual int random_nb(int max, int min) = 0;
    virtual void write_scores(const char *username) = 0;
    virtual int right_ghost(struct ghost *ghost, int *move_order) = 0;
    virtual int left_ghost(struct ghost *ghost, int *move_order) = 0;
    virtual int down_ghost(struct ghost *ghost, int *move_order) = 0;
    virtual int up_ghost(struct ghost *ghost, int *move_order) = 0;
};

extern "C" std::unique_ptr<IPacmanLib> make_pacman_instance();
